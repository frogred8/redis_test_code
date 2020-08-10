local a = KEYS[1];
local b = KEYS[2];
local count = tonumber(ARGV[1]);
if count > 10 then
    redis.breakpoint()
    redis.call('set', a, count)
else
    redis.call('set', b, count);
end
return true;