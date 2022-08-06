declare class MMKVModule {
  initializeMMKV: (rootDir: string) => void;
  setString: (key: string, value: string) => boolean | undefined;
  getString: (key: string) => string | undefined;
  setBoolean: (key: string, value: boolean) => boolean | undefined;
  getBoolean: (key: string) => boolean | undefined;
  setNumber: (key: string, value: number) => boolean | undefined;
  getNumber: (key: string) => number | undefined;

  containsKey: (key: string) => boolean | undefined;
  getKeys: () => string[] | undefined;
  removeKey: (key: string) => void;
  clearMemoryCache: () => void;
  clearAll: () => void;
}
