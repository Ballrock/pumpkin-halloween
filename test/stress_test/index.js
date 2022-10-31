import { SerialPort } from 'serialport';
import { ReadlineParser } from '@serialport/parser-readline';

// Create a port
const port = new SerialPort({
    // path: '/dev/cu.usbserial-0001',
    path: '/dev/cu.usbserial-14310',
    baudRate: 115200,
})

const getDisplay = function () {
    const number = Math.floor(Math.random() * (9));
    switch (number) {
        case 0:
            return 'test';
        case 1:
            return 'off';
        case 2:
            return 'emergency';
        case 3:
            return 'entry';
        case 4:
            return 'exit';
        case 5:
            return 'entry-exit';
        case 6:
            return 'entry-ok';
        case 7:
            return 'exit-ok';
        case 8:
            return 'entry-no';
        case 9:
            return 'exit-no';
        default:
            return 'unknown';
    }
}

const parser = port.pipe(new ReadlineParser({ delimiter: '\r\n' }))
parser.on('data', console.log)
parser.on('error', console.error);

let number = 0;
setInterval(() => {
    const display = getDisplay();
    console.log(`Stress-Test sending ${display}`);
    port.write(`${display}\n`);
    console.log(`Passage ${number++}`)
}, 1000);