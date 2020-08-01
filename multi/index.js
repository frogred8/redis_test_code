const Redis = require('redis');
const redis = Redis.createClient();

redis.watch('name', 'age');
// redis.set('age', 20);
redis
    .multi()
    .set('name', 'abc', (err, ret) => { console.log('set name'); for(var i=0; i<2000000000; i++);; })
    .get('name', (err, ret) => { console.log('get name:', ret); })
    .set('age', 30, (err, ret) => { console.log('set age'); })
    .get('age', (err, ret) => { console.log('get age:', ret); })
    .exec((err, replies) => {
        if (!replies) {
            console.log('watching key was changed.');
            return;
        }
        replies.forEach((reply, idx) => {
            console.log(idx, ':', reply);
        })
    });
