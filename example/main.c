/**
 *
 * Copyright 2005 LogicBlaze Inc.
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 */

#include <stdlib.h>
#include "stomp.h"

int die(int exitCode, const char *message, apr_status_t reason) {
    char msgbuf[80];
	apr_strerror(reason, msgbuf, sizeof(msgbuf));
	fprintf(stderr, "%s: %s (%d)\n", message, msgbuf, reason);
	exit(exitCode);
	return reason;
}

static void terminate()
{
   apr_terminate();
}

int main(int argc, char *argv[])
{
   apr_status_t rc;
   apr_pool_t *pool;
   stomp_connection *connection;
   
   setbuf(stdout, NULL);
   
   rc = apr_initialize();
	rc==APR_SUCCESS || die(-2, "Could not initialize", rc);
   atexit(terminate);	
   
   rc = apr_pool_create(&pool, NULL);
	rc==APR_SUCCESS || die(-2, "Could not allocate pool", rc);
   
   fprintf(stdout, "Connecting......");
   rc=stomp_connect( &connection, "activemq1", 61613, pool);
	rc==APR_SUCCESS || die(-2, "Could not connect", rc);
   fprintf(stdout, "OK\n");
      
   fprintf(stdout, "Sending connect message.");
   {
      stomp_frame frame;
      frame.command = "CONNECT";
      frame.headers = apr_hash_make(pool);
      apr_hash_set(frame.headers, "login", APR_HASH_KEY_STRING, "hchirino");          
      apr_hash_set(frame.headers, "passcode", APR_HASH_KEY_STRING, "letmein");          
      frame.body = NULL;
	  frame.body_length = -1;
      rc = stomp_write(connection, &frame, pool);
      rc==APR_SUCCESS || die(-2, "Could not send frame", rc);
   }  
   fprintf(stdout, "OK\n");   
   fprintf(stdout, "Reading Response.");
   {
      stomp_frame *frame;
      rc = stomp_read(connection, &frame, pool);
      rc==APR_SUCCESS || die(-2, "Could not read frame", rc);
      fprintf(stdout, "Response: %s, %s\n", frame->command, frame->body);
   }     
   fprintf(stdout, "OK\n");

   fprintf(stdout, "Sending Subscribe.");
   {
      stomp_frame frame;
      frame.command = "SUB";
      frame.headers = apr_hash_make(pool);
      apr_hash_set(frame.headers, "destination", APR_HASH_KEY_STRING, "/queue/FOO.BAR");      
	  frame.body_length = -1;
      frame.body = NULL;
      rc = stomp_write(connection, &frame, pool);
      rc==APR_SUCCESS || die(-2, "Could not send frame", rc);
   }  
   fprintf(stdout, "OK\n");
   
   fprintf(stdout, "Sending Message.");
   {
      stomp_frame frame;
      frame.command = "SEND";
      frame.headers = apr_hash_make(pool);
      apr_hash_set(frame.headers, "destination", APR_HASH_KEY_STRING, "/queue/FOO.BAR");
      
      frame.body_length = -1;
	  frame.body = "This is the message";
      rc = stomp_write(connection, &frame, pool);
      rc==APR_SUCCESS || die(-2, "Could not send frame", rc);
   }  
   fprintf(stdout, "OK\n");
   
   fprintf(stdout, "Reading Response.");
   {
      stomp_frame *frame;
      rc = stomp_read(connection, &frame, pool);
      rc==APR_SUCCESS || die(-2, "Could not read frame", rc);
      fprintf(stdout, "Response: %s, %s\n", frame->command, frame->body);
   }     
   fprintf(stdout, "OK\n");
   

   fprintf(stdout, "Sending Disconnect.");
   {
      stomp_frame frame;
      frame.command = "DISCONNECT";
      frame.headers = NULL;
	  frame.body_length = -1;
      frame.body = NULL;
      rc = stomp_write(connection, &frame, pool);
      rc==APR_SUCCESS || die(-2, "Could not send frame", rc);
   }  
   fprintf(stdout, "OK\n");
   
   fprintf(stdout, "Disconnecting...");
	rc=stomp_disconnect(&connection); 
	rc==APR_SUCCESS || die(-2, "Could not disconnect", rc);
   fprintf(stdout, "OK\n");
   
   apr_pool_destroy(pool);	   
   return 0;
}
