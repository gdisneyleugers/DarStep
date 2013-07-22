/** Interface for DKPortNameServer for NSConnection integration.
   Copyright (C) 2011 Free Software Foundation, Inc.

   Written by:  Niels Grewe <niels.grewe@halbordnung.de>
   Created: February 2011

   This library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2 of the License, or (at your option) any later version.

   This library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Library General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with this library; if not, write to the Free
   Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02111 USA.
   */

#import <Foundation/NSObject.h>
#import <DBusKit/DKPort.h>
#include <stdint.h>

@class DKPort, NSHashTable, NSMutableDictionary, NSRecursiveLock, NSString;

enum
{
  DKPortNameAllowReplacement = 1 << 0,
  DKPortNameDoNotQueue = 1 << 1,
  DKPortNameReplaceExisting = 1 << 2,
  DKPortNameFlagMax = 7
};

typedef NSUInteger DKPortNameFlags;

@interface DKPortNameServer: NSObject
{
  @private
  /**
   * The type of the well-known bus that the nameserver is responsible for.
   */
  DKDBusBusType busType;

  /**
   * Contains all names the local connection is queued for. They will
   * become active names once the present owner and all preceding members of the
   * queue have ceased using the name.
   */
  NSHashTable *queuedNames;

  /**
   * Contains all names active for the local connection.
   */
  NSHashTable *activeNames;

  /**
   * The lock protecting the tables.
   */
   NSRecursiveLock *lock;
}

+ (id)sharedSystemBusPortNameServer;

+ (id)sharedSessionBusPortNameServer;

+ (id)sharedPortNameServerForBusType: (DKDBusBusType)type;

- (DKPort*)portForName: (NSString*)name;

- (BOOL)registerPort: (DKPort*)port
                name: (NSString*)name;

- (BOOL)registerPort: (DKPort*)port
                name: (NSString*)name
	       flags: (DKPortNameFlags)flags;

- (void)removePortForName: (NSString*)name;
@end
