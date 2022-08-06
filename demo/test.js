const MMKVModule = require("../");
const path = require("path");

console.log("MMKVModule", MMKVModule);
const instance = new MMKVModule();

console.log("initializeMMKV");
instance.initializeMMKV(path.join(__dirname, "./mmkv"));

console.log("setString", "testKey", "123456789");
instance.setString("testKey", "123456789");

const result = instance.getString("testKey");
console.log("getString1", result);
console.log(instance.removeKey("testKey"));
console.log("getString2", instance.getString("testKey"));

console.log(instance.setBoolean("isTest", false));
console.log(instance.getBoolean("isTest"));
console.log(instance.getBoolean("isTest2"));

console.log(instance.getNumber("testNumber"));
console.log(instance.setNumber("testNumber", 2333.33333));
console.log(instance.getNumber("testNumber"));

console.log(instance.containsKey("testContainsKey"));
console.log(instance.containsKey("testNumber"));

console.log(instance.getKeys());
