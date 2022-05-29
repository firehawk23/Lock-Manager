# Lock Manager

compile the code using g++ -std=c++11 -o lm lockmanager.cpp
run the code using ./lm
6 cases were tried using switch case.

Example output :

1. Txn waits for X-lock on item asks for s-lock on same item held by s-lock. 
2. Txn asks for X-lock on item is held by s-lock and is only txn 
3. Txn waits for X-lock on item is held by x-lock on diff item held by s-lock.. 
4. Unlock txn in wait queue. 
5. X-lock and s-lock waits on same item Txn can't accept further requests for same item. 
6. Unlock used on empty locktable 
Enter a choice : 4

request from txn_id 1234 for EXCLUSIVE lock on resource AAA...
EXCLUSIVE lock GRANTED for txnId 1234 on resource AAA

-------------------------- resource_name: AAA --------------------------
TxnId: 1234			EXCLUSIVE			GRANTED
------------------------------------------------------------------------

request from txn_id 4567 for SHARED lock on resource AAA...
SHARED lock WAITING for txnId 4567 on resource AAA

-------------------------- resource_name: AAA --------------------------
TxnId: 1234			EXCLUSIVE			GRANTED
TxnId: 4567			SHARED				WAITING
------------------------------------------------------------------------

request from txn_id 4567 for unlocking resource AAA...
cannot be unlocked as txnId 4567 is not holding the lock
could not unlock WAITING for txnId 4567 on resource AAA

-------------------------- resource_name: AAA --------------------------
TxnId: 1234			EXCLUSIVE			GRANTED
TxnId: 4567			SHARED				WAITING
------------------------------------------------------------------------