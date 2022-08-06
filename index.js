const { MMKVModule } = require("bindings")("node-mmkv");

console.log("MMKVModule", MMKVModule);
const instance = new MMKVModule();

console.log("initializeMMKV");
instance.initializeMMKV();

console.log("setString", "testKey", "123456789");
instance.setString("testKey", "123456789");

const result = instance.getString("testKey");
console.log("getString", result);

console.log(instance);
