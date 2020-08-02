redis.call('set', KEYS[1], ARGV[1])
local changeCount = redis.call('incr', KEYS[1] .. ':change_count');
return changeCount