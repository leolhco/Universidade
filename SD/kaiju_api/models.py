from datetime import datetime
from config import db, ma

class Kaiju(db.Model):
    __tablename__ = "kaiju"
    id = db.Column(db.Integer, primary_key=True)
    name = db.Column(db.String(32), unique=True)
    power = db.Column(db.String(32))
    timestamp = db.Column(
        db.DateTime, default=datetime.utcnow, onupdate=datetime.utcnow
    )

class KaijuSchema(ma.SQLAlchemyAutoSchema):
    class Meta:
        model = Kaiju
        load_instance = True
        sqla_session = db.session

kaiju_schema = KaijuSchema()
kaijus_schema = KaijuSchema(many=True)