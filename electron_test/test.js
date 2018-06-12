// index.js
var ipc = require('electron').ipcRenderer;

var button1 = document.getElementById('tile1');
button1.onclick = function() {
  // now what?
  console.log("Try to pin 1");
  ipc.send('pin-tile1', 0);
}

var button2 = document.getElementById('tile2');
button2.onclick = function() {
  // now what?
  console.log("Try to pin 2 ");
  ipc.send('pin-tile2', 0);
}

var button3 = document.getElementById('tile3');
button3.onclick = function() {
  // now what?
  console.log("Try to pin 3 ");
  ipc.send('pin-tile3', 0);
}

var button4 = document.getElementById('tile4');
button4.onclick = function() {
  // now what?
  console.log("Try to pin 4 ");
  ipc.send('pin-tile4', 0);
}

var button5 = document.getElementById('tile5');
button5.onclick = function() {
  // now what?
  console.log("Try to pin 5 ");
  ipc.send('pin-tile5', 0);
}

var button_exist1 = document.getElementById('tile1-exist');
button_exist1.onclick = function() {
  console.log("check 1");
  ipc.send('check-tile', 'tile-1');
}

var button_exist2 = document.getElementById('tile2-exist');
button_exist2.onclick = function() {
  console.log("check 2");
  ipc.send('check-tile', 'tile-2');
}

var button_exist3 = document.getElementById('tile3-exist');
button_exist3.onclick = function() {
  console.log("check 3");
  ipc.send('check-tile', 'tile-3');
}

var button_exist4 = document.getElementById('tile4-exist');
button_exist4.onclick = function() {
  console.log("check 4");
  ipc.send('check-tile', 'tile-4');
}
var button_exist5 = document.getElementById('tile5-exist');
button_exist5.onclick = function() {
  console.log("check 5");
  ipc.send('check-tile', 'tile-5');
}



var button_delete1 = document.getElementById('tile1-delete');
button_delete1.onclick = function() {
  console.log("delete 1");
  ipc.send('delete-tile', 'tile-1');
}

var button_delete2 = document.getElementById('tile2-delete');
button_delete2.onclick = function() {
  console.log("delete 2");
  ipc.send('delete-tile', 'tile-2');
}

var button_delete3 = document.getElementById('tile3-delete');
button_delete3.onclick = function() {
  console.log("delete 3");
  ipc.send('delete-tile', 'tile-3');
}

var button_delete4 = document.getElementById('tile4-delete');
button_delete4.onclick = function() {
  console.log("delete 4");
  ipc.send('delete-tile', 'tile-4');
}

var button_delete5 = document.getElementById('tile5-delete');
button_delete5.onclick = function() {
  console.log("delete 5");
  ipc.send('delete-tile', 'tile-5');
}

var button_update5 = document.getElementById('tile5-update');
button_update5.onclick = function() {
  console.log("update  5");
  ipc.send('update-tile5', '');
}

var button_notify1 = document.getElementById('tile1-notify');
button_notify1.onclick = function() {
  console.log("tile1-notify");
  ipc.send('tile1-notify', '');
}

var button_notify2 = document.getElementById('tile1-badge');
button_notify2.onclick = function() {
  console.log("tile1-badge");
  ipc.send('tile1-badge', '');
}

var button_notify3 = document.getElementById('tile1-clear-notification');
button_notify3.onclick = function() {
  console.log("tile1-clear-notification");
  ipc.send('tile1-clear-notification', '');
}

var button_notify4 = document.getElementById('tile1-clear-badge');
button_notify4.onclick = function() {
  console.log("tile1-clear-badge");
  ipc.send('tile1-clear-badge', '');
}

