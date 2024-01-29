from flask import Flask, request, jsonify, render_template
from flask_cors import CORS  # Import CORS

app = Flask(__name__)
CORS(app)  # Enable CORS for all routes

sensorValue = None  # Initialize sensorValue

@app.route('/update', methods=['POST'])
def update_post():
    global sensorValue
    print("TESTING POST REQ .. ")
    sensorValue = request.form.get('value')
    if sensorValue is not None:
        print("POSTING A NOTIFICATION ORDER & TEMP VALUE REQUEST:", sensorValue)
        return jsonify({'status': 'success'}), 200  # HTTP 200 OK
    else:
        return jsonify({'status': 'failed', 'error': 'Invalid request'}), 400  # HTTP 400 Bad Request

@app.route('/update', methods=['GET'])
def update():
    global sensorValue
    return jsonify({'PATIENT TEMPvalue': sensorValue})
    print("TESTING GET REQ.. ")
    sensorValue = request.args.get('value')
    if sensorValue is not None:
        print("GOT PATIENT'S TEMP VALUE:", sensorValue)
        return ('OK GOT IT' +sensorValue)
        return jsonify({'status': 'notify'}), 200 # HTTP 200 ok
    else:
        return jsonify({'status': 'failed', 'error': 'Invalid request'}), 400  # HTTP 400 Bad Request

@app.route('/')
def index():
    return render_template('index.html', sensorValue=sensorValue)
if __name__ == '__main__':
    app.run(host='192.168.1.2', port=5000)
