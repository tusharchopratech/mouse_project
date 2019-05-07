'use strict';


console.log("Tushar1");

const ioHook = require('iohook');

console.log("Tushar2");
ioHook.start(true);
ioHook.on('mouseclick', event => {
    console.log('mouseclick : ',JSON.stringify(event)); // { type: 'mousemove', x: 700, y: 400 }
});
ioHook.on('mousedown', event => {
    console.log('mousedown : ',JSON.stringify(event)); // { type: 'mousemove', x: 700, y: 400 }
});
ioHook.on('mouseup', event => {
    console.log('mouseup : ',JSON.stringify(event)); // { type: 'mousemove', x: 700, y: 400 }
});