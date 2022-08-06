# node-mmkv

Base on [Tencent MMKV](https://github.com/Tencent/MMKV) high-performance key-value storage framework. Implement Node.js.

# Status

__It is in the experimental stage, please do not use it in production environment.__

# Dependencies

- Node.js v16.x, NAPI version 8
- cmake

# Usage

```bash
const MMKVModule = require("node-mmkv");
const path = require("path");

const mmkv = new MMKVModule();

mmkv.initializeMMKV(path.join(__dirname, "./mmkv"));
```

## API

### initializeMMKV(rootDir: string)

Initial MMKV framework instance. `rootDir` is a absolute path string.

### setString: (key: string, value: string) => boolean | undefined;

Set a string value to storage.

### getString: (key: string) => string | undefined;

Get a string value from storage.

### setBoolean: (key: string, value: boolean) => boolean | undefined;

Set a boolean value to storage.

### getBoolean: (key: string) => boolean | undefined;

Get a boolean value from storage.

### setNumber: (key: string, value: number) => boolean | undefined;

Set a number value to storage.

### getNumber: (key: string) => number | undefined;

Get a number value from storage.

### containsKey: (key: string) => boolean | undefined;

Check if the given key exists in storage.

### getKeys: () => string[] | undefined;

Get all keys from storage.

### removeKey: (key: string) => void;

Remove given key and value in storage.

### clearMemoryCache: () => void;

Clear memory cache.

### clearAll: () => void;

Clear all keys and values in storage.

# License

This library is licensed under the MIT license.
