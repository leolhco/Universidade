from flask import abort, make_response
from config import db
from models import Kaiju, kaijus_schema, kaiju_schema


def read_all():
    kaijus = Kaiju.query.all()
    return kaijus_schema.dump(kaijus)

def create(kaiju):
    name = kaiju.get("name")
    existing_kaiju = Kaiju.query.filter(Kaiju.name == name).one_or_none()

    if existing_kaiju is None:
        new_kaiju = kaiju_schema.load(kaiju, session=db.session)
        db.session.add(new_kaiju)
        db.session.commit()
        return kaiju_schema.dump(new_kaiju), 201
    else:
        abort(406, f"Kaiju com o nome {name} já existe")

def read_one(name):
    kaiju = Kaiju.query.filter(Kaiju.name == name).one_or_none()

    if kaiju is not None:
        return kaiju_schema.dump(kaiju)
    else:
        abort(404, f"Kaiju com o nome {name} não encontrado")  

def update(name, kaiju):
    existing_kaiju = Kaiju.query.filter(Kaiju.name == name).one_or_none()

    if existing_kaiju:
        update_kaiju = kaiju_schema.load(kaiju, session=db.session)
        existing_kaiju.power = update_kaiju.power
        db.session.merge(existing_kaiju)
        db.session.commit()
        return kaiju_schema.dump(existing_kaiju), 201
    else:
        abort(404, f"Kaiju com o nome {name} não encontrado")  

def delete(name):
    existing_kaiju = Kaiju.query.filter(Kaiju.name == name).one_or_none()

    if existing_kaiju:
        db.session.delete(existing_kaiju)
        db.session.commit()
        return make_response(f"{name} deletado com sucesso", 200)
    else:
        abort(404, f"Kaiju com o nome {name} não encontrado")