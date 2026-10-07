from flask import Flask, request, jsonify
from flask_cors import CORS
import random

app = Flask(__name__)
CORS(app)

@app.route('/')
def home():
    return "Hello World"

@app.route('/api/w')
def api_hello():
    number = random.randint(1, 100)
    return jsonify({"number": number})

if __name__ == "__main__":
    app.run(debug=True, port=5000)
