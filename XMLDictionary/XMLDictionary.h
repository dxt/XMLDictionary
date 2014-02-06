//
//  XMLDictionary.h
//
//  Version 1.3
//
//  Created by Nick Lockwood on 15/11/2010.
//  Copyright 2010 Charcoal Design. All rights reserved.
//
//  Get the latest version of XMLDictionary from here:
//
//  https://github.com/nicklockwood/XMLDictionary
//
//  This software is provided 'as-is', without any express or implied
//  warranty.  In no event will the authors be held liable for any damages
//  arising from the use of this software.
//
//  Permission is granted to anyone to use this software for any purpose,
//  including commercial applications, and to alter it and redistribute it
//  freely, subject to the following restrictions:
//
//  1. The origin of this software must not be misrepresented; you must not
//  claim that you wrote the original software. If you use this software
//  in a product, an acknowledgment in the product documentation would be
//  appreciated but is not required.
//
//  2. Altered source versions must be plainly marked as such, and must not be
//  misrepresented as being the original software.
//
//  3. This notice may not be removed or altered from any source distribution.
//

#import <Foundation/Foundation.h>


typedef enum
{
    XMLDictionaryAttributesModePrefixed = 0, //default
    XMLDictionaryAttributesModeDictionary,
    XMLDictionaryAttributesModeUnprefixed,
    XMLDictionaryAttributesModeDiscard
}
XMLDictionaryAttributesMode;


typedef enum
{
    XMLDictionaryNodeNameModeRootOnly = 0, //default
    XMLDictionaryNodeNameModeAlways,
    XMLDictionaryNodeNameModeNever
}
XMLDictionaryNodeNameMode;


static NSString *const XMLDictionaryAttributesKey   = @"__attributes";
static NSString *const XMLDictionaryCommentsKey     = @"__comments";
static NSString *const XMLDictionaryTextKey         = @"__text";
static NSString *const XMLDictionaryNodeNameKey     = @"__name";
static NSString *const XMLDictionaryAttributePrefix = @"_";


@interface XMLDictionaryParser : NSObject <NSCopying>

+ (XMLDictionaryParser *)sharedInstance;

@property (nonatomic, assign) BOOL collapseTextNodes; // defaults to YES
@property (nonatomic, assign) BOOL stripEmptyNodes;   // defaults to YES
@property (nonatomic, assign) BOOL trimWhiteSpace;    // defaults to YES
@property (nonatomic, assign) BOOL alwaysUseArrays;   // defaults to NO
@property (nonatomic, assign) BOOL preserveComments;  // defaults to NO

@property (nonatomic, assign) XMLDictionaryAttributesMode attributesMode;
@property (nonatomic, assign) XMLDictionaryNodeNameMode nodeNameMode;

- (NSDictionary *)dictionaryWithData:(NSData *)data;
- (NSDictionary *)dictionaryWithString:(NSString *)string;
- (NSDictionary *)dictionaryWithFile:(NSString *)path;

@end


@interface NSDictionary (XMLDictionary)

+ (NSDictionary *)xd_dictionaryWithXMLData:(NSData *)data;
+ (NSDictionary *)xd_dictionaryWithXMLString:(NSString *)string;
+ (NSDictionary *)xd_dictionaryWithXMLFile:(NSString *)path;

- (NSDictionary *)xd_attributes;
- (NSDictionary *)xd_childNodes;
- (NSArray *)xd_comments;
- (NSString *)xd_nodeName;
- (NSString *)xd_innerText;
- (NSString *)xd_innerXML;
- (NSString *)xd_XMLString;

- (NSArray *)xd_arrayValueForKeyPath:(NSString *)keyPath;
- (NSString *)xd_stringValueForKeyPath:(NSString *)keyPath;
- (NSDictionary *)xd_dictionaryValueForKeyPath:(NSString *)keyPath;

@end


@interface NSString (XMLDictionary)

- (NSString *)xd_XMLEncodedString;

@end

@interface NSMutableDictionary (XMLDictionary)

//- (void)xd_setName:(NSString *)name;
- (void)xd_addAttribute:(NSString *)value withName:(NSString *)name;
- (void)xd_setText:(NSString *)text;
- (void)xd_addElement:(id)element withName:(NSString *)name;

+ (NSMutableDictionary *)xd_rootDictionaryWithName:(NSString *)name andBlock:(void(^)(NSMutableDictionary *root))block;
- (void)xd_addElementWithName:(NSString *)name text:(NSString *)text andBlock:(void(^)(NSMutableDictionary *element))block;
- (void)xd_addElementWithName:(NSString *)name text:(NSString *)text xmlnsAttribute:(NSString *)xmlnsAttribute andBlock:(void(^)(NSMutableDictionary *element))block;

@end

