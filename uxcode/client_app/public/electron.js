// Modules to control application life and create native browser window
const { app, BrowserWindow } = require('electron');
const ipc = require('electron').ipcMain;

const path = require('path');
const url = require('url');
const isDev = require('electron-is-dev');

var child = require('child_process').execFile;
var isBackendRunning = false;
var backendRunningIndex = 1;
var maxBackendRunningTry = 5;

var isSocketConnect = false;
var socketConnectionIndex = 1;
var maxSocketConnectionTry = 5;

var process_to_kill = [];

var net = require('net');
var client = new net.Socket();
var socketData = null;
var startReceivingRealTimeData = false;

let mainWindow

function createWindow() {

  mainWindow = new BrowserWindow({
    width: 800,
    height: 600,
    title: "Desktop App",
    webPreferences: {
      nodeIntegration: true
    }
  })

  mainWindow.loadURL(isDev ? 'http://localhost:3000' : `file://${path.join(__dirname, '../build/index.html')}`);
  mainWindow.on('closed', function () {
    mainWindow = null
  })

  startBackend();
}

function startBackend() {

  var error = false;

  var processData = child("../../wearablecode/windows/src/main.exe", function (err, data) {
    if (err) {
      console.error("Backend Connection Error : ", err);
      error = true;
    } else {
      error = false;
    }
  });

  if (error) {
    isBackendRunning = false;
    if (backendRunningIndex < maxBackendRunningTry) {
      backendRunningIndex += 1;
      console.log('Retrying Backend Connection...');
      startBackend();
    } else {
      console.log("Maximum attempt to start backedn reached.");
      app.quit();
    }
  } else {
    console.log('Backend Connected !!!');
    setTimeout(connectSocket, 5000);
    isBackendRunning = true;
    process_to_kill.push(processData.pid);
  }

}

function connectSocket() {

  client.connect(27015, 'localhost', function () {
    console.log('Socket Connected !!!');
    isSocketConnect = true;
    client.write('real_time_data');
  });

  client.on('data', function (data) {

    socketData = new Buffer(data).toString('ascii');
    mainWindow.webContents.send('real_time_data', socketData);
    if (startReceivingRealTimeData) {
      client.write('real_time_data');
    }
    // console.log(socketData);
    // while (isDataArrayFree() == false) {
    // }
    // var status = tcpScoketData("write", data);
    // if (status != 1) {
    //   while (status != 1) {
    //     status = tcpScoketData("write", data);
    //   }
    // // }
    // client.write('real_time_data');
  });

  client.on('close', function () {
    isSocketConnect = false;
    console.log('Socket Closed...');
  });

  client.on('error', function (err) {
    isSocketConnect = false;
    console.error("Socket Connection Error : ", err);
  });
}

ipc.on('socket_data_send', (event, data) => {
  if (data == "real_time_data") {
    startReceivingRealTimeData = true;
    client.write('real_time_data');
  } else {
    startReceivingRealTimeData = false;
  }
})


app.on('ready', createWindow)

app.on('window-all-closed', function () {
  if (process.platform !== 'darwin') app.quit()
})

app.on('activate', function () {
  if (mainWindow === null) createWindow()
})

app.on('before-quit', function () {

});

app.on('window-all-closed', function () {
  for (var i = 0; i < process_to_kill.length; i++) {
    var kill = require('tree-kill');
    kill(process_to_kill[i]);
  }
  process_to_kill = [];
});

