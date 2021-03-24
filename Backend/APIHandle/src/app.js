import logger from 'morgan';
import express from 'express';
//const cors = require('cors');
import cors from 'cors'
//var mysql = require('mysql') // import mysql module

import cookieParser from 'cookie-parser';
import indexRouter from './routes/index';




//import cashHandleRouter from './routes/index';
const app = express();
//app.use(logger('dev'));//uncomment to enable GET POST LOGS
app.use(cors());
app.use(express.json());
app.use(express.urlencoded({ extended: true }));
app.use(cookieParser());
app.use('/v1', indexRouter);
//app.use('/v1', indexRouter);




export default app;