//var http = require('http');  
var express = require('express');
var app = express();

var devices = [
   {"name": "droid", "uuid": "1475133249668276300",
    "HWInfo":{
              "address": {"host": "127.0.0.1" ,"mac": "08:90:a2:bf","port":0},
              "capacity": {"cpu": {"cores": 2,"index": 50},"ram": 40960000,"storage": {"total": 8012000,"used": 3264000}}
             },
     "Images": { "application": {"name": "application","url": "docker://repository/branch/app/url","Config": "configuration string for application"},
                 "plate": {"name": "plate","url": "docker://repository/branch/service/plate/url","Config": "configuration string for plate recognition"}
                },
     "job": {"name": "plate","status": "running","pid": 3610,"starttime": 14898738674989234,"Image": null}
   },
   {"name": "robot","uuid": "1475133250123458300",
    "HWInfo":{
              "address": {"host": "127.0.0.1" ,"mac": "08:90:a2:bf","port":0},
              "capacity": {"cpu": {"cores": 2,"index": 50},"ram": 40960000,"storage": {"total": 8012000,"used": 3264000}}
             },
     "Images": { "application": {"name": "application","url": "docker://repository/branch/app/url","Config": "configuration string for application"},
                 "plate": {"name": "plate","url": "docker://repository/branch/service/plate/url","Config": "configuration string for plate recognition"}
                },
     "job": {"name": "plate","status": "running","pid": 3610,"starttime": 14898738674989234,"Image": null}
   }
];

var images= [
   {"name":"mirror", "url":"docker://repository/branch/app/url", "Config":"configuration string for application"},
   {"name":"eye", "url":"docker://repository/branch/app/url", "Config":"configuration string for application"},
   {"name":"application", "url":"docker://repository/branch/app/url", "Config":"configuration string for application"}
];

app.all('*', function(req, res, next) {  
    res.header("Access-Control-Allow-Origin", "*");  
    res.header("Access-Control-Allow-Headers", "X-Requested-With");  
    res.header("Access-Control-Allow-Methods","PUT,POST,GET,DELETE,OPTIONS");  
    res.header("X-Powered-By",' 3.2.1')  
    res.header("Content-Type", "application/json;charset=utf-8");  
    next();  
}); 

app.get('/devices',function(req, res){
    res.set({'Content-Type':'text/json','Encodeing':'utf8'});  
    res.send(devices)  
})  

app.get('/images',function(req, res){
    res.set({'Content-Type':'text/json','Encodeing':'utf8'});  
    res.send(images)
})  

//app.get('/devices/:id',function(req, res){ 
//    res.set({'Content-Type':'text/json','Encodeing':'utf8'});  
//    res.send(map[req.param('id')])  
//    //console.log(req.param('id'))  
//})  
//
//app.post('/devices/', express.bodyParser(), function(req, res){ 
//    res.set({'Content-Type':'text/json','Encodeing':'utf8'});  
//    map[req.body.id] = req.body  
//    res.send({status:"success",url:"/devices/"+req.body.id}) 
//})  
//
//app.put('/devices/:id', express.bodyParser(), function(req, res){ 
//    res.set({'Content-Type':'text/json','Encodeing':'utf8'});  
//    map[req.body.id] = req.body  
//    res.send({status:"success",url:"/devices/"+req.param('id'),device:req.body});  
//})  
//
//app.delete('/devices/:id',function(req, res){
//    res.set({'Content-Type':'text/json','Encodeing':'utf8'});  
//    delete map[req.param('id')]  
//    res.send({status:"success",url:"/devices/"+req.param('id')})  
//    console.log(map)  
//})  

app.listen(8080);
