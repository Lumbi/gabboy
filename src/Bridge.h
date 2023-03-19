//
//  Bridge.h
//  gabboy
//
//  Created by Gabriel Lumbi on 2023-03-17.
//

#ifndef Bridge_h
#define Bridge_h

#ifdef __OBJC__

#import <Foundation/Foundation.h>

@interface Bridge : NSObject

- (void) load;

- (void) frame;

- (unsigned char *) lcd;

@end

#endif

#endif /* Bridge_h */
