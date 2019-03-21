const mongoose = require('mongoose');

const dataStructure = mongoose.Schema({
    data: [{
        Node_1: [{
            sensor_1: { type: Number },
            sensor_2: { type: Number },
            sensor_3: { type: Number },
            sensor_4: { type: Number }
        }],
        Node_2: [{
            sensor_1: { type: Number },
            sensor_2: { type: Number },
            sensor_3: { type: Number },
            sensor_4: { type: Number }
        }],
        Node_3: [{
            sensor_1: { type: Number },
            sensor_2: { type: Number },
            sensor_3: { type: Number },
            sensor_4: { type: Number }
        }],
        Node_4: [{
            sensor_1: { type: Number },
            sensor_2: { type: Number },
            sensor_3: { type: Number },
            sensor_4: { type: Number }
        }],
        Node_5: [{
            sensor_1: { type: Number },
            sensor_2: { type: Number },
            sensor_3: { type: Number },
            sensor_4: { type: Number }
        }]
    }]
})

module.exports = mongoose.model('Data', dataStructure);