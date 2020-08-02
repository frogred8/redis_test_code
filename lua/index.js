const fs = require('fs');
const { promisify } = require('util');
const redis = require('redis').createClient();

const redis_script = promisify(redis.script).bind(redis);
const redis_evalsha = promisify(redis.evalsha).bind(redis);
const redis_eval = promisify(redis.eval).bind(redis);
const redis_get = promisify(redis.get).bind(redis);

(async () => {
    const lua_str = fs.readFileSync('test.lua').toString();
    console.log('# lua file\n' + lua_str, '\n');

    console.log('# using eval');
    const ret1 = await redis_eval(lua_str, 1, 'name', 'john');
    const val1 = await redis_get('name');
    console.log('name:', val1)
    console.log('changed:', ret1, '\n');

    console.log('# using evalsha');
    const lua_sha = await redis_script('load', lua_str);
    console.log('lua_sha:', lua_sha);
    const ret2 = await redis_evalsha(lua_sha, 1, 'name', 'steve');
    const val2 = await redis_get('name');
    console.log('name:', val2);
    console.log('changed:', ret2);
})();