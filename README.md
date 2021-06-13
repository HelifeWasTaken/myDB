# myDB
Todo:
- Json Parser Done
- Json Deserializer Done
- Database Handler Done

```json
➜  myDB git:(main) ✗ ./myDB
> ls
build     castle.json     compile_flags.txt  input  lol.json  myDB   README.md  vgcore.132709
build.sh  CMakeLists.txt  include            log    main.cpp  NewDB  src
> cat lol.json
{"john":[{"toto":42,"tata":52},["lol","aled","mdr"],42]}
> loadFile lol lol.json
File: [lol.json] sucessfully loaded as [lol]
> dump lol
{
    "john": [{
        "tata": 52,
        "toto": 42
    },
    ["lol", "aled", "mdr"], 42]
}
> dump lol john[0]
{
    "tata": 52,
    "toto": 42
}
> dump lol john[0].tata
52
> loadFile castle castle.json
File: [castle.json] sucessfully loaded as [castle]
> save AnAnotherDB
Appending to DB (every collections with the same name will be overwritten)
Successfully written: [AnAnotherDB/castle.json]
Successfully written: [AnAnotherDB/lol.json]
> exit
Leaving DB
➜  myDB git:(main) ✗ ls
AnAnotherDB  build.sh     CMakeLists.txt     include  log       main.cpp  NewDB      src
build        castle.json  compile_flags.txt  input    lol.json  myDB      README.md  vgcore.132709
➜  myDB git:(main) ✗ ls AnAnotherDB
castle.json  lol.json
➜  myDB git:(main) ✗ ./myDB
> loadDB AnAnotherDB
File: [AnAnotherDB/lol.json] sucessfully loaded as [lol]
File: [AnAnotherDB/castle.json] sucessfully loaded as [castle]
> collections
castle
lol
> dump lol
{
    "john": [{
        "tata": 52,
        "toto": 42
    },
    ["lol", "aled", "mdr"], 42]
}
> delete lol
> collections
castle
> exit
Leaving DB
```
