const mongoose = require('mongoose');

const dataStructure = mongoose.Schema({
    node0: {
        data0: { type: String },
        data1: { type: String },
        retry: { type: String }
    },
    node1: {
        data0: { type: String },
        data1: { type: String },
        retry: { type: String }
    },
    centralName: { type: String },
    date: { type: Date },
    time: { type: String },
    packets: { type: Number }
})

module.exports = mongoose.model('Data', dataStructure);