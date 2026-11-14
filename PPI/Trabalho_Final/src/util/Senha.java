package util;

import java.nio.charset.StandardCharsets;
import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;
import java.security.SecureRandom;
import java.util.Base64;

/**
 * Gera e confere o hash das senhas.
 *
 * A senha NUNCA e gravada em texto puro no banco. O que vai para a coluna
 * conta.senha e a string "salt:hash", onde:
 *   - salt = 16 bytes aleatorios (Base64), diferente para cada conta
 *   - hash = SHA-256 aplicado sobre (salt + senha), em Base64
 *
 * O salt impede que duas contas com a mesma senha gerem o mesmo hash e
 * inviabiliza o uso de tabelas prontas (rainbow tables).
 *
 * Em um sistema real o recomendado seria BCrypt/Argon2 (algoritmos lentos
 * de proposito). Aqui usamos SHA-256 por vir pronto no proprio Java, sem
 * precisar adicionar biblioteca externa ao projeto.
 */
public final class Senha {

    private static final SecureRandom RANDOM = new SecureRandom();

    private Senha() {
    }

    /** Recebe a senha digitada e devolve "salt:hash" para gravar no banco. */
    public static String gerarHash(String senhaPura) {
        byte[] salt = new byte[16];
        RANDOM.nextBytes(salt);

        String saltBase64 = Base64.getEncoder().encodeToString(salt);
        String hashBase64 = hash(saltBase64, senhaPura);

        return saltBase64 + ":" + hashBase64;
    }

    /** Confere a senha digitada contra o valor "salt:hash" vindo do banco. */
    public static boolean conferir(String senhaPura, String valorArmazenado) {
        if (senhaPura == null || valorArmazenado == null) {
            return false;
        }

        String[] partes = valorArmazenado.split(":");
        if (partes.length != 2) {
            return false;
        }

        String saltBase64 = partes[0];
        String hashEsperado = partes[1];
        String hashCalculado = hash(saltBase64, senhaPura);

        // Comparacao em tempo constante (evita timing attack).
        return MessageDigest.isEqual(
                hashEsperado.getBytes(StandardCharsets.UTF_8),
                hashCalculado.getBytes(StandardCharsets.UTF_8));
    }

    private static String hash(String saltBase64, String senhaPura) {
        try {
            MessageDigest digest = MessageDigest.getInstance("SHA-256");
            digest.update(saltBase64.getBytes(StandardCharsets.UTF_8));
            byte[] bytes = digest.digest(senhaPura.getBytes(StandardCharsets.UTF_8));
            return Base64.getEncoder().encodeToString(bytes);
        } catch (NoSuchAlgorithmException e) {
            throw new RuntimeException("Algoritmo SHA-256 nao disponivel na JVM.", e);
        }
    }
}
