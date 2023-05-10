const MMKVModule = require('../index');
const path = require('path');

describe('MMKVModule', () => {
  let mmkvModule;

  beforeEach(() => {
    const options = {
      rootDir: path.join(__dirname, "./storage"),
      id: 'mmkv.test',
      multiProcess: false,
      cryptKey: 'encryption-key',
    };
    mmkvModule = new MMKVModule(options);
  });

  afterEach(() => {
    // Clean up any resources after each test
    mmkvModule.clearAll();
  });

  describe('setString', () => {
    it('should set a string value for the given key', () => {
      const result = mmkvModule.setString('key1', 'value1');
      expect(result).toBe(true);
    });

    it('should return undefined if the key or value is undefined', () => {
      const result1 = mmkvModule.setString(undefined, 'value1');
      expect(result1).toBeUndefined();

      const result2 = mmkvModule.setString('key1', undefined);
      expect(result2).toBeUndefined();
    });
  });

  describe('getString', () => {
    it('should return the string value for the given key', () => {
      mmkvModule.setString('key1', 'value1');
      const result = mmkvModule.getString('key1');
      expect(result).toBe('value1');
    });

    it('should return undefined if the key does not exist', () => {
      const result = mmkvModule.getString('nonExistingKey');
      expect(result).toBeUndefined();
    });
  });

  describe('setBoolean', () => {
    it('should set a boolean value for the given key', () => {
      const result = mmkvModule.setBoolean('key1', true);
      expect(result).toBe(true);
    });

    it('should return undefined if the key is undefined', () => {
      const result = mmkvModule.setBoolean(undefined, true);
      expect(result).toBeUndefined();
    });
  });

  describe('getBoolean', () => {
    it('should return the boolean value for the given key', () => {
      mmkvModule.setBoolean('key1', true);
      const result = mmkvModule.getBoolean('key1');
      expect(result).toBe(true);
    });

    it('should return undefined if the key does not exist', () => {
      const result = mmkvModule.getBoolean('nonExistingKey');
      expect(result).toBeUndefined();
    });
  });

  describe('setNumber', () => {
    it('should set a number value for the given key', () => {
      const result = mmkvModule.setNumber('key1', 42);
      expect(result).toBe(true);
    });

    it('should return undefined if the key is undefined', () => {
      const result = mmkvModule.setNumber(undefined, 42);
      expect(result).toBeUndefined();
    });
  });

  describe('getNumber', () => {
    it('should return the number value for the given key', () => {
      mmkvModule.setNumber('key1', 42);
      const result = mmkvModule.getNumber('key1');
      expect(result).toBe(42);
    });

    it('should return undefined if the key does not exist', () => {
      const result = mmkvModule.getNumber('nonExistingKey');
      expect(result).toBeUndefined();
    });
  });

  describe('containsKey', () => {
    it('should return true if the key exists', () => {
      mmkvModule.setString('key1', 'value1');
      const result = mmkvModule.containsKey('key1');
      expect(result).toBe(true);
    });
    
    it('should return false if the key does not exist', () => {
      const result = mmkvModule.containsKey('nonExistingKey');
      expect(result).toBe(false);
    });
  });

  describe('getKeys', () => {
    it('should return an array of all keys', () => {
      mmkvModule.setString('key1', 'value1');
      mmkvModule.setBoolean('key2', true);
      mmkvModule.setNumber('key3', 42);
      const result = mmkvModule.getKeys();
      expect(result).toEqual(['key3', 'key2', 'key1']);
    });

    it('should return an empty array if no keys exist', () => {
      const result = mmkvModule.getKeys();
      expect(result).toEqual([]);
    });
  });

  describe('removeKey', () => {
    it('should remove the key and its value', () => {
      mmkvModule.setString('key1', 'value1');
      mmkvModule.removeKey('key1');
      const result = mmkvModule.getString('key1');
      expect(result).toBeUndefined();
    });
  });
  
  describe('clearMemoryCache', () => {
    it('should clear the memory cache', () => {
      mmkvModule.setString('key1', 'value1');
      mmkvModule.clearMemoryCache();
      const result = mmkvModule.getString('key1');
      expect(result).toEqual('value1');
    });
  });

  describe('clearAll', () => {
    it('should clear all keys and values', () => {
      mmkvModule.setString('key1', 'value1');
      mmkvModule.setBoolean('key2', true);
      mmkvModule.setNumber('key3', 42);
      mmkvModule.clearAll();
      const result1 = mmkvModule.getString('key1');
      const result2 = mmkvModule.getBoolean('key2');
      const result3 = mmkvModule.getNumber('key3');
      expect(result1).toBeUndefined();
      expect(result2).toBeUndefined();
      expect(result3).toBeUndefined();
    });
  });
});
