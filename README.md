# redis test code

```
# make & run

1. multi
> cd multi; node index.js

2. lua
> cd lua; node index.js

3. module
> cd module; make
> redis-cli module load test_module.so

4. twemproxy
> cd twemproxy
> docker pull softonic/twemproxy
> docker run -d -p 20000:20000 --network redis_net -v `pwd`/conf/nutcracker.yml:/conf/nutcracker.yml softonic/twemproxy nutcracker
```
