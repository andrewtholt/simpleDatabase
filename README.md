Small, simple, key value database.

Branches:

* PubSub
  master
  noMalloc

The pubsub branch contains the basis of a public subscribe system

When a keys value is updated a callback (updateCallback) is executed.

This is defines as 'weak' and can be over riden by an application.

The callback expects a char pointer to the key, the value and an integer identifying the
recipient.


