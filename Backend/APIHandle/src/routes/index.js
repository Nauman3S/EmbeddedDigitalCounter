import express from 'express';
import { indexPage } from '../controllers';
import { cashHandlePage } from '../controllers';
import mysql from 'mysql'
//import MqttHandler from './mqtt_handler'
import mqtt from 'mqtt';
const indexRouter = express.Router();
const cashHandleRouter = express.Router();


//const mqtt = require('mqtt')
const client = mqtt.connect('mqtt://broker.hivemq.com')

var garageState = ''
var connected = false

client.on('connect', () => {
  client.subscribe('edc-monitor/getActive')
  client.subscribe('edc-monitor/setActive')
  client.subscribe('edc-monitor/createNew')
  client.subscribe('edc-monitor/updatePlayer')
})


var db = mysql.createConnection({
  host: 'srv-captain--vb-mysqldb-db',
  port:3306,
  user: 'root',
  password: 'vb-mysqldb',
  database: 'edc_monitor'
})
db.connect(function(err) {
  if (err) throw err;
  console.log("Connected!");
});



indexRouter.get('/', indexPage);
indexRouter.get('/csh', cashHandlePage);

indexRouter.get('/listAll', function(req, res) {
  
  let sql = `SELECT * FROM data`;
  db.query(sql, function(err, data, fields) {
    if (err) throw err;
    res.json({
      status: 200,
      data,
      message: "User lists retrieved successfully"
    })
  })
});

indexRouter.get('/getActive', function(req, res) {
  let sql = `SELECT * FROM data WHERE ActiveStatus='1'`;
  db.query(sql, function(err, data, fields) {
    if (err) throw err;
    res.json({
      status: 200,
      data,
      message: "User lists retrieved successfully"
    })
  })
});



indexRouter.post('/addPlayer', function(req, res) {
  let sql = `INSERT INTO data(Timestamp, PlayerID, TMIN30, TMOUT30, TMIND, TMOUTD, ActiveStatus) VALUES (?)`;
  let values = [
    req.body.Timestamp,
    req.body.PlayerID,
    req.body.TMIN30,
    req.body.TMOUT30,
    req.body.TMIND,
    req.body.TMOUTD,
    req.body.ActiveStatus
    
  ];
  db.query(sql, [values], function(err, data, fields) {
    if (err) throw err;
    res.json({
      status: 200,
      message: "New player added successfully"
    })
  })
});



client.on('message', (topic, message) => {
  switch (topic) {
    case 'edc-monitor/getActive':
      
      handlegetActive()
      .then(function(results){
        var strData=JSON.stringify(results[0])
        client.publish('edc-monitor/activePlayer', strData)
        
      })
      .catch(function(err){
        console.log("Promise rejection error: "+err);
      })

    case 'edc-monitor/setActive':
      handleDeactivateAll()
      .then(function(results){
        var strData=JSON.stringify(results[0])
        // client.publish('edc-monitor/activePlayer', strData)
        handlesetActive(message).then(function(results){var m=""}).catch(function(err){console.log(err)});
        
      })
      .catch(function(err){
        console.log("Promise rejection error: "+err);
      })
      // client.publish('garage/close', 'Closing;'+message)
      // return handleGarageState(message)
    case 'edc-monitor/createNew':
      var dataD=message.toString()
      console.log(dataD)
      var DataG=dataD.split(';')
      handleCreateNew(DataG[0],DataG[1],DataG[2],DataG[3],DataG[4],DataG[5],DataG[6])
      .then(function(results){
        var strData=JSON.stringify(results[0])
        //client.publish('edc-monitor/activePlayer', strData)
        
      })
      .catch(function(err){
        console.log("Promise rejection error: "+err);
      })

    case 'edc-monitor/updatePlayer':
      var dataD=message.toString()
      console.log(dataD)
      var DataG=dataD.split(';')
      handleUpdatePlayer(DataG[0],DataG[1],DataG[2],DataG[3],DataG[4],DataG[5],DataG[6])
      .then(function(results){
        var strData=JSON.stringify(results[0])
        //client.publish('edc-monitor/activePlayer', strData)
        
      })
      .catch(function(err){
        console.log("Promise rejection error: "+err);
      })
  }
  //console.log('No handler for topic %s', topic)
})
//import async from 'async';
 function handlegetActive(){
  return new Promise(function(resolve, reject){
    db.query(
      `SELECT * FROM data WHERE ActiveStatus='1'`, 
        function(err, rows){                                                
            if(rows === undefined){
                reject(new Error("Error rows is undefined"));
            }else{
                resolve(rows);
            }
        }
    )}
)}

function handleDeactivateAll(){
  return new Promise(function(resolve, reject){
    db.query(
      `UPDATE data SET ActiveStatus='0' WHERE ActiveStatus='1'`, 
        function(err, rows){                                                
            if(rows === undefined){
                reject(new Error("Error rows is undefined"));
            }else{
                resolve(rows);
            }
        }
    )}  
)}
function handlesetActive(playerID){
  return new Promise(function(resolve, reject){
    db.query(
      `UPDATE data SET ActiveStatus='1' WHERE PlayerID='`+playerID+`'`, 
        function(err, rows){                                                
            if(rows === undefined){
                reject(new Error("Error rows is undefined"));
            }else{
                resolve(rows);
            }
        }
    )}  
)}

function handleCreateNew(Timestamp,PlayerID,TMIN30,TMOUT30,TMIND,TMOUTD,ActiveStatus){
  return new Promise(function(resolve, reject){
  let sql = `INSERT INTO data(Timestamp, PlayerID, TMIN30, TMOUT30, TMIND, TMOUTD, ActiveStatus) VALUES (?)`;
  let values = [
            Timestamp,
            PlayerID,
            TMIN30,
            TMOUT30,
            TMIND,
            TMOUTD,
            ActiveStatus
    
  ];
    db.query(sql,[values],
        function(err, rows){                                                
            if(rows === undefined){
                reject(new Error("Error rows is undefined"));
            }else{
                resolve(rows);
            }
        }
    )}  
)}

function handleUpdatePlayer(playerID,Timestamp,TMIN30,TMOUT30,TMIND,TMOUTD,ActiveStatus){
  return new Promise(function(resolve, reject){
    
    db.query(
      `UPDATE data SET Timestamp='`+Timestamp+`', TMIN30='`+TMIN30+`', TMOUT30='`+TMOUT30+`', TMIND='`+TMIND+`', TMOUTD='`+TMOUTD+`', ActiveStatus='`+ActiveStatus+`' WHERE PlayerID='`+playerID+`'`, 
        function(err, rows){                                                
            if(rows === undefined){
                reject(new Error("Error rows is undefined"));
            }else{
                resolve(rows);
            }
        }
    )}  
)}



export default indexRouter;
//export default cashHandleRouter;