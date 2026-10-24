'''
Diogo Cruz Koichi Yonemoto - 12311BCC010
Leonardo Henrique Carvalho Oliveira - 12311BCC003
'''

from flask import render_template
import config
from models import Kaiju

app = config.connex_app

app.add_api(config.basedir / "swagger.yml")

@app.route("/")
def home():
    kaijus = Kaiju.query.all()
    return render_template("home.html", kaijus=kaijus)

if __name__ == "__main__":
    app.run(host="0.0.0.0", port=8000, debug=True)