const { app, BrowserWindow } = require('electron');
const ipc = require('electron').ipcMain;
var process = require('process');
const path = require('path');
const isDev = require('electron-is-dev');
var kill = require('tree-kill');
var child = require('child_process').execFile;
var net = require('net');
var client = new net.Socket();


var process_to_kill = [];
var startReceivingRealTimeData = false;
let mainWindow

var backEndPath;
global.shared_object = {current_envirnoment: process.env.NODE_ENV};


if (process.env.NODE_ENV == "dev") {
  backEndPath = "./src/extra-resources/main.exe"; // For Dev
} else {
  backEndPath = "./resources/src/extra-resources/main.exe"; // For Prod
}



function createWindow() {
  mainWindow = new BrowserWindow({
    width: 800,
    height: 600,
    title: "Desktop App", webPreferences: {
      nodeIntegration: true
    }
  })
  mainWindow.loadURL(isDev ? 'http://localhost:3000' : `file://${path.join(__dirname, '../build/index.html')}`);
  mainWindow.on('closed', function () {
    mainWindow = null
  });
  // connectSocket();
}

ipc.on('socket_data_send', (event, data) => {
  if (data == "start_raw_real_time_data") {
    startReceivingRealTimeData = true;
    client.write(JSON.stringify({ type: 'message', value: 'raw_real_time_data' }) + '*****');
  } else if (data == "stop_raw_real_time_data") {
    startReceivingRealTimeData = false;
  } else if (data == "start_training") {
    client.write(JSON.stringify({ type: 'message', value: 'start_training' }) + '*****');
  } else if (data == "stop_training") {
    client.write(JSON.stringify({ type: 'message', value: 'stop_training' }) + '*****');
  }
});

ipc.on('internal_ipc', (event, data) => {

  if (data == "start_backend_and_socket") {
    if (process.env.NODE_ENV == "dev") {
      setTimeout(connectSocket, 3000);
    } else {
      for (var i = 0; i < process_to_kill.length; i++) {
        try {
          kill(process_to_kill[i]);
        } catch (err) {
          console.log(err);
        }
      }
      process_to_kill = [];
      setTimeout(startBackend, 3000);
    }
  }
});

app.on('ready', createWindow)

app.on('window-all-closed', function () {
  if (process.platform !== 'darwin') app.quit()
});

app.on('activate', function () {
  if (mainWindow === null) createWindow()
});

app.on('before-quit', function () {

});

app.on('window-all-closed', function () {
  for (var i = 0; i < process_to_kill.length; i++) {
    kill(process_to_kill[i], 'SIGKILL', function (err) {
      console.log("Error : ", err);
    });
  }
  process_to_kill = [];
});



function startBackend() {
  var error = false;
  var processData = child(backEndPath, function (err, data) {
    if (err) {
      mainWindow.webContents.send('internal_ipc', JSON.stringify({ type: 'error', value: err }));
      error = true;
    } else {
      error = false;
    }
  });

  if (error) {
    mainWindow.webContents.send('internal_ipc', JSON.stringify({ type: 'status', value: 'backend_connection_error' }));
  } else {
    mainWindow.webContents.send('internal_ipc', JSON.stringify({ type: 'status', value: 'backend_connected' }));
    process_to_kill.push(processData.pid);
    setTimeout(connectSocket, 3000);
  }
}

function connectSocket() {
  client = null;
  client = new net.Socket();
  client.connect(27015, 'localhost', function () {
    mainWindow.webContents.send('internal_ipc', JSON.stringify({ type: 'status', value: 'socket_connected' }));
    mainWindow.webContents.send('internal_ipc', JSON.stringify({ type: 'current_envirnoment', value: process.env.NODE_ENV }));
  });

  client.on('data', function (data) {
    // console.log(String(data), " at ", new Date().getTime());
    if (startReceivingRealTimeData) {
      // client.write('raw_real_time_data' + '*****');
      client.write(JSON.stringify({ type: 'message', value: 'raw_real_time_data' }) + '*****');
    }
    if (mainWindow != null) {
      mainWindow.webContents.send('socket_data_received', new Buffer(data).toString('ascii'));
    }
  });

  client.on('close', function () {
    isSocketConnect = false;
    if (mainWindow != null) {
      mainWindow.webContents.send('internal_ipc', JSON.stringify({ type: 'status', value: 'socket_disconnected' }));
    }
  });

  client.on('error', function (err) {
    // isSocketConnect = false;
    // console.error("Socket Connection Error : ", err);
    if (mainWindow != null) {
      mainWindow.webContents.send('internal_ipc', err);
    }
  });
}