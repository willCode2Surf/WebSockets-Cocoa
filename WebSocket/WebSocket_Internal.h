//
//  WebSocket_Internal.h
//  WebSocket
//
//  Created by Jens Alfke on 9/10/13.
//  Copyright (c) 2013 Couchbase. All rights reserved.

#import "WebSocket.h"
#import "GCDAsyncSocket.h"
#import "Logging.h"


#define TIMEOUT_NONE          -1
#define TIMEOUT_DEFAULT       60
#define TIMEOUT_REQUEST_BODY  10

// WebSocket frame types:
#define WS_OP_CONTINUATION_FRAME   0
#define WS_OP_TEXT_FRAME           1
#define WS_OP_BINARY_FRAME         2
#define WS_OP_CONNECTION_CLOSE     8
#define WS_OP_PING                 9
#define WS_OP_PONG                 10

#define HTTPLogTrace() LogTo(@"WS", @"TRACE: %s", __func__ )
#define HTTPLogTraceWith(MSG, PARAM...) LogTo(@"WS", @"TRACE: %s " MSG, __func__, PARAM)

enum {
    TAG_HTTP_REQUEST_HEADERS = 300,
    TAG_HTTP_RESPONSE_HEADERS,
};


@interface WebSocket () <GCDAsyncSocketDelegate>
{
@protected
	__weak id<WebSocketDelegate> _delegate;
	dispatch_queue_t _websocketQueue;
	GCDAsyncSocket *_asyncSocket;

    WebSocketState _state;
//	BOOL _isStarted;
//	BOOL _isOpen;
    BOOL _isClient;
}

- (void) start;

- (void) sendFrame: (NSData*)msgData type: (unsigned)type tag: (long)tag;

@end
