const express = require('express');
const router = express.Router();
const passport = require('passport')
const Node = require('../schema/NodeSchema');
const jwt = require('jsonwebtoken');
const config = require('../config/config');
const mongoose = require('mongoose');

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


module.exports = router;