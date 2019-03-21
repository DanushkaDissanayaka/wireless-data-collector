const express = require('express');
const router = express.Router();
const passport = require('passport')
const jwt = require('jsonwebtoken');
const config = require('../config/config');
const mongoose = require('mongoose');
const dynamic_schemas = require('mongoose-dynamic-schemas');

const Data = require('../schema/dataschema');
const Node = require('../schema/NodeSchema');



router.post('/addNewNode',function(req,res,next){
    let newNode = new Node({
        nodeId:req.body.nodeId,
    }
    );
    Node.addNode(newNode,function(err,node){
        if (err) {
            res.json({success:false , msg:err});
        }
        else{
            res.json({success:true , msg:"Node added"});
        }
    });
});

router.post('/addData',function(req,res,next){
    const nodeId = req.body.nodeId;
    let data = new Data ({
        Data:req.body.Data
    });
})

router.post('/addNewCollector',function(req,res,next){

});

//testing dynamic schema
router.post('/addNode', (req, res, next) => {
    const nodeNumber = req.body.nodeNumber;
    Data
        .then(result => {
            dynamic_schemas.addSchemaField(Data.data, "Node_"+nodeNumber, [{ sensor_1: Number, sensor_2: Number, sensor_3: Number, sensor_4: Number }] )
        })
        .catch(err => {
            if(err){
                res.status(500).json({
                    state: false
                })
            } else{
                res.status(200).json({
                    state: true
                })
            }
        })
})

module.exports = router;