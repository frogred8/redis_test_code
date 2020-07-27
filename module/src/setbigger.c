#include <stdlib.h>
#include "redismodule.h"

#define BIND_COMMAND(ctx, name, func) (RedisModule_CreateCommand((ctx), #name, (func), "write deny-oom", 1, 1, 1) == REDISMODULE_OK)


int SetBigger(RedisModuleCtx *ctx,
              RedisModuleString **argv, int argc) {
    RedisModule_AutoMemory(ctx);
    if (argc != 3) return RedisModule_WrongArity(ctx);

    int mode = REDISMODULE_READ | REDISMODULE_WRITE;

    RedisModuleKey *keyA = RedisModule_OpenKey(ctx, argv[1], mode);
    RedisModuleKey *keyB = RedisModule_OpenKey(ctx, argv[2], mode);
    
    size_t bufA_len, bufB_len;
    const char *bufA =  RedisModule_StringDMA(keyA, &bufA_len, REDISMODULE_READ);
    const char *bufB =  RedisModule_StringDMA(keyB, &bufB_len, REDISMODULE_READ);
    int64_t numA = atoll(bufA);
    int64_t numB = atoll(bufB);
    int64_t max = numA > numB ? numA : numB;

    RedisModuleString *out = RedisModule_CreateStringFromLongLong(ctx, max);
    if (numA < numB) RedisModule_StringSet(keyA, out);
    else if (numA > numB) RedisModule_StringSet(keyB, out);

    RedisModule_ReplicateVerbatim(ctx);
    RedisModule_ReplyWithLongLong(ctx, max);
    return REDISMODULE_OK;
}

int RedisModule_OnLoad(RedisModuleCtx *ctx,
        RedisModuleString **argv, int argc) {
    uint8_t ret;
    ret = RedisModule_Init(ctx, "test_module", 1, REDISMODULE_APIVER_1);
    if (ret == REDISMODULE_ERR) return REDISMODULE_ERR;

    if (RedisModule_CreateCommand(ctx,
                                  "setbigger",
                                  SetBigger,
                                  "write deny-oom",
                                  1, 1, 1) == REDISMODULE_ERR) {
        return REDISMODULE_ERR;
    }
    return REDISMODULE_OK;
}
