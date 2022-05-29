/* 
Goal : Build a lock manager. 
The lock manager should support the following capabilities:
1. Lock a resource in either shared or exclusive mode. 
2. Unlock a resource held by a transaction. 
A resource will be identified by a 10 character string. 
*/

#include <iostream>
#include <unordered_map>
#include <list>
#include <algorithm>      // for std::find
#include <iterator>       // for std::advance
#include <typeinfo>

using namespace std;

// Abstraction of a resource that can be locked. 
// A resource is locked in a 'mode' by a 'transaction'. 
// The lock request may be granted or put on wait based
// on a lock compatibility matrix. 
class lockable_resource
{
private:
  uint32_t txn_id_;
  uint8_t lock_type_; // SHARED, EXCLUSIVE
  uint8_t lock_status_; // GRANTED, WAITING
public:
  lockable_resource(
    uint32_t txn_id,
    uint8_t lock_type,
    uint8_t lock_status):
    txn_id_(txn_id),
    lock_type_(lock_type),
    lock_status_(lock_status)
  {}
  uint8_t getLockType() 
  {
    return(lock_type_);
  }
  uint8_t getLockStatus()
  {
    return(lock_status_);
  }
  uint32_t getTxnId()
  {
    return(txn_id_);
  }
  bool setLockStatus(uint8_t st)
  {
    lock_status_ = st;
  }
  uint8_t setLockType(uint8_t lt)
  {
    lock_type_ = lt;
  }

};

enum lockType
{
  SHARED,
  EXCLUSIVE
};
enum lockStatus
{
  GRANTED,
  WAITING
};

// Resource
// type of lock
// txnid

bool lock(std::string resource_name, 
          std::uint32_t txn_id,
          uint8_t lock_type);

uint8_t unlock(std::string resource_name,
              std::uint32_t txn_id);

void printList(std::string resource_name);

unordered_map<std::string, list<lockable_resource *>*> lock_table;

void case1()
{
  uint8_t ret = lock("AAA", 1234, lockType::SHARED);
  if(ret == lockStatus::GRANTED)
  {
    std::cout << "SHARED lock GRANTED for txnId " << 1234 << " on resource AAA" << std::endl;
  }
  else
  {
    std::cout << "SHARED lock WAITING for txnId " << 1234 << " on resource AAA" << std::endl;
  }
  printList("AAA");
  // next call
  ret = lock("AAA", 4567, lockType::EXCLUSIVE);
  if(ret == lockStatus::GRANTED)
  {
    std::cout << "EXCLUSIVE lock GRANTED for txnId " << 4567 << " on resource AAA" << std::endl;
  }
  else
  {
    std::cout << "EXCLUSIVE lock WAITING for txnId " << 4567 << " on resource AAA" << std::endl;
  }
  printList("AAA");
  // next call
  ret = lock("AAA", 4657, lockType::SHARED);
  if(ret == lockStatus::GRANTED)
  {
    std::cout << "SHARED lock GRANTED for txnId " << 4657 << " on resource AAA" << std::endl;
  }
  else
  {
    std::cout << "SHARED lock WAITING for txnId " << 4657 << " on resource AAA" << std::endl;
  }
  printList("AAA");
  // next call
  ret = lock("AAA", 4567, lockType::SHARED);
  if(ret == lockStatus::GRANTED)
  {
    std::cout << "SHARED lock GRANTED for txnId " << 4567 << " on resource AAA" << std::endl;
  }
  else
  {
    std::cout << "SHARED lock WAITING for txnId " << 4567 << " on resource AAA" << std::endl;
  }
  printList("AAA");
}

void case2()
{
  uint8_t ret = lock("AAA", 1234, lockType::SHARED);
  if(ret == lockStatus::GRANTED)
  {
    std::cout << "SHARED lock GRANTED for txnId " << 1234 << " on resource AAA" << std::endl;
  }
  else
  {
    std::cout << "SHARED lock WAITING for txnId " << 1234 << " on resource AAA" << std::endl;
  }
  printList("AAA");

  //next call
  ret = lock("AAA", 1234, lockType::EXCLUSIVE);
  if(ret == lockStatus::GRANTED)
  {
    std::cout << "EXCLUSIVE lock GRANTED for txnId " << 1234 << " on resource AAA" << std::endl;
  }
  else
  {
    std::cout << "EXCLUSIVE lock WAITING for txnId " << 1234 << " on resource AAA" << std::endl;
  }
  printList("AAA");
}

void case3()
{
  uint8_t ret = lock("AAA", 1234, lockType::EXCLUSIVE);
  if(ret == lockStatus::GRANTED)
  {
    std::cout << "EXCLUSIVE lock GRANTED for txnId " << 1234 << " on resource AAA" << std::endl;
  }
  else
  {
    std::cout << "EXCLUSIVE lock WAITING for txnId " << 1234 << " on resource AAA" << std::endl;
  }
  printList("AAA");
  // next call
  ret = lock("AAA", 4567, lockType::EXCLUSIVE);
  if(ret == lockStatus::GRANTED)
  {
    std::cout << "EXCLUSIVE lock GRANTED for txnId " << 4567 << " on resource AAA" << std::endl;
  }
  else
  {
    std::cout << "EXCLUSIVE lock WAITING for txnId " << 4567 << " on resource AAA" << std::endl;
  }
  printList("AAA");
  // next call
  ret = lock("AAA", 4567, lockType::SHARED);
  if(ret == lockStatus::GRANTED)
  {
    std::cout << "SHARED lock GRANTED for txnId " << 4567 << " on resource AAA" << std::endl;
  }
  else
  {
    std::cout << "SHARED lock WAITING for txnId " << 4567 << " on resource AAA" << std::endl;
  }
  printList("AAA");
}

void case4()
{
  uint8_t ret = lock("AAA", 1234, lockType::EXCLUSIVE);
  if(ret == lockStatus::GRANTED)
  {
    std::cout << "EXCLUSIVE lock GRANTED for txnId " << 1234 << " on resource AAA" << std::endl;
  }
  else
  {
    std::cout << "EXCLUSIVE lock WAITING for txnId " << 1234 << " on resource AAA" << std::endl;
  }
  printList("AAA");
  // next call
  ret = lock("AAA", 4567, lockType::SHARED);
  if(ret == lockStatus::GRANTED)
  {
    std::cout << "SHARED lock GRANTED for txnId " << 4567 << " on resource AAA" << std::endl;
  }
  else
  {
    std::cout << "SHARED lock WAITING for txnId " << 4567 << " on resource AAA" << std::endl;
  }
  printList("AAA");
  //next call
  ret = unlock("AAA", 4567);
  if(ret == true)
  {
    std::cout << "unlocked for txnId " << 4567 << " on resource AAA" << std::endl;
  }
  else
  {
    std::cout << "could not unlock WAITING for txnId " << 4567 << " on resource AAA" << std::endl;
  }

  // next call
  printList("AAA");
}

void case5()
{
  uint8_t ret = lock("AAA", 1234, lockType::EXCLUSIVE);
  if(ret == lockStatus::GRANTED)
  {
    std::cout << "EXCLUSIVE lock GRANTED for txnId " << 1234 << " on resource AAA" << std::endl;
  }
  else
  {
    std::cout << "EXCLUSIVE lock WAITING for txnId " << 1234 << " on resource AAA" << std::endl;
  }
  printList("AAA");
  // next call
  ret = lock("AAA", 4567, lockType::EXCLUSIVE);
  if(ret == lockStatus::GRANTED)
  {
    std::cout << "EXCLUSIVE lock GRANTED for txnId " << 4567 << " on resource AAA" << std::endl;
  }
  else
  {
    std::cout << "EXCLUSIVE lock WAITING for txnId " << 4567 << " on resource AAA" << std::endl;
  }
  printList("AAA");
  // next call
  ret = lock("AAA", 4567, lockType::SHARED);
  if(ret == lockStatus::GRANTED)
  {
    std::cout << "SHARED lock GRANTED for txnId " << 4567 << " on resource AAA" << std::endl;
  }
  else
  {
    std::cout << "SHARED lock WAITING for txnId " << 4567 << " on resource AAA" << std::endl;
  }
  printList("AAA");
  // next call
  ret = lock("AAA", 4567, lockType::SHARED);
  if(ret == lockStatus::GRANTED)
  {
    std::cout << "SHARED lock GRANTED for txnId " << 4567 << " on resource AAA" << std::endl;
  }
  else
  {
    std::cout << "SHARED lock WAITING for txnId " << 4567 << " on resource AAA" << std::endl;
  }
  printList("AAA");
  ret = lock("AAA", 4567, lockType::EXCLUSIVE);
  if(ret == lockStatus::GRANTED)
  {
    std::cout << "EXCLUSIVE lock GRANTED for txnId " << 4567 << " on resource AAA" << std::endl;
  }
  else
  {
    std::cout << "EXCLUSIVE lock WAITING for txnId " << 4567 << " on resource AAA" << std::endl;
  }
  printList("AAA");
}

void case6()
{
  uint8_t ret = unlock("AAA", 1234);
}

int main()
{
  uint32_t ch;
  std::cout << "1. Txn waits for X-lock on item asks for s-lock on same item held by s-lock. "<<endl;//granted s-lock,x-lock waits in queue
  std::cout << "2. Txn asks for X-lock on item is held by s-lock and is only txn "<<endl;//update lock_type
  std::cout << "3. Txn waits for X-lock on item is held by x-lock on diff item held by s-lock.. "<<endl;//wait in queue
  std::cout << "4. Unlock txn in wait queue. "<<endl; //we can't remove a transaction in wait queue
  std::cout << "5. X-lock and s-lock waits on same item Txn can't accept further requests for same item. "<<endl;
  std::cout << "6. Unlock used on empty locktable "<<endl;//error handling
  std::cout << "Enter a choice : ";
  std::cin >> ch;
  std::cout<<endl;
  switch(ch)
  {
    case 1:
      case1();
      break;
    case 2:
      case2();
      break;
    case 3:
      case3();
      break;
    case 4:
      case4();
      break;
    case 5:
      case5();
      break;
    case 6:
      case6();
      break;
    default:
      std::cerr<<"ERROR: Invalid option.Try again!"<<endl;
      break;
  } 
  return 0;

}

bool lock(std::string resource_name,
          std::uint32_t txn_id,
          uint8_t lock_type)
{
  if(lock_type == lockType::SHARED)
    std::cout << "request from txn_id " << txn_id << " for SHARED lock on resource " << resource_name << "...\n";
  else
    std::cout << "request from txn_id " << txn_id << " for EXCLUSIVE lock on resource " << resource_name << "...\n";
  
  uint8_t retval = lockStatus::WAITING;
  
  lockable_resource *lr = new lockable_resource(txn_id, lock_type, lockStatus::GRANTED);
  // if resource is not present in the lock_table
  if(lock_table.find(resource_name) == lock_table.end())
  {
    list<lockable_resource*> *lst = new list<lockable_resource*>;
    lst->emplace_back(lr);
    lock_table[resource_name] = lst;
    retval = lockStatus::GRANTED;
  }
  else
  {
  std::list<lockable_resource*>::iterator findIter_granted = lock_table[resource_name]->begin();

  for( ; findIter_granted != lock_table[resource_name]->end(); findIter_granted++)
  {
    if((*findIter_granted)->getTxnId() == txn_id && (*findIter_granted)->getLockStatus() == lockStatus::GRANTED)
        break;
  }


  lr->setLockStatus(lockStatus::WAITING);
  std::list<lockable_resource*>::iterator findIter_waiting = lock_table[resource_name]->begin();
  for( ; findIter_waiting != lock_table[resource_name]->end(); findIter_waiting++)
  {
    if((*findIter_waiting)->getTxnId() == txn_id && (*findIter_waiting)->getLockStatus() == lockStatus::WAITING)
        break;
  }  
    // txnid is asking for resource for the first time
    if(findIter_granted == lock_table[resource_name]->end() && findIter_waiting == lock_table[resource_name]->end())
    {
      std::list<lockable_resource*>::iterator iter = lock_table[resource_name]->begin();
      if((*iter)->getLockType() == lockType::EXCLUSIVE)
      {
        if((*iter)->getLockStatus() == lockStatus::GRANTED)
        {
          lock_table[resource_name]->emplace_back(lr);               
          retval = lockStatus::WAITING;                                 
        }
        else
        {
          if(lock_type == lockType::SHARED)
          {
            lr->setLockStatus(lockStatus::GRANTED);
            lock_table[resource_name]->emplace_back(lr);              
            retval = lockStatus::GRANTED;                             
          }
          else
          {
            lr->setLockStatus(lockStatus::WAITING);
            lock_table[resource_name]->emplace_back(lr);
            retval = lockStatus::WAITING;
          }
        }
      }
      else
      {
        if(lock_type == lockType::SHARED)
        {
          lr->setLockStatus(lockStatus::GRANTED);
          lock_table[resource_name]->emplace_back(lr);
          retval = lockStatus::GRANTED;                                 
        }
        else
        {
          lr->setLockStatus(lockStatus::WAITING);
          lock_table[resource_name]->emplace_back(lr);
          retval = lockStatus::WAITING;                                       
        }
      }
    }

    // txnid has already asked for this resource
    else
    {
      // txnid was GRANTED the lock on the resource
      if(findIter_granted != lock_table[resource_name]->end())
      {
        // txnid has the lock of type EXCLUSIVE
        if((*findIter_granted)->getLockType() == lockType::EXCLUSIVE)
        {
       
          retval = (*findIter_granted)->getLockStatus();
        }

        // txnid has lock of type SHARED
        else
        {
          // txnid is asking for SHARED
          if(lock_type == lockType::SHARED)
          {
            
            retval = (*findIter_granted)->getLockStatus();        
          }
          // txnid is asking for EXCLUSIVE
          else
          {
            std::list<lockable_resource*>::iterator tmp = findIter_granted;
            if(findIter_granted == lock_table[resource_name]->begin() && (++findIter_granted) == lock_table[resource_name]->end())
            {
              (*tmp)->setLockType(lockType::EXCLUSIVE);
              retval = lockStatus::GRANTED;
            }
            else
            {
              lr->setLockStatus(lockStatus::WAITING);
              lock_table[resource_name]->emplace_back(lr);
              retval = lockStatus::WAITING;                         
            }
          }
        }
      }

      // txnid was set to WAITING status
      else
      {
        // already WAITING on what txnid asked for
        if((*findIter_waiting)->getLockType() == lock_type)
        {
          // DO NOTHING
          retval = (*findIter_waiting)->getLockStatus();                  // DONE (FALSE LOCKING)
        }

        // txnid waiting for EXCLUSIVE and asked for SHARED
        else if((*findIter_waiting)->getLockType() == lockType::EXCLUSIVE && lock_type == lockType::SHARED)
        {
          bool already_for_sharing = false;
          std::list<lockable_resource*>::iterator frst = lock_table[resource_name]->begin();
          if((*frst)->getTxnId() != txn_id && (*frst)->getLockType() == lockType::EXCLUSIVE && (*frst)->getLockStatus() == lockStatus::GRANTED)
          {
            for(; frst != lock_table[resource_name]->end(); frst++)
              if((*frst)->getTxnId() == txn_id && (*frst)->getLockType() == lockType::SHARED && (*frst)->getLockStatus() == lockStatus::WAITING)
              {
                already_for_sharing = true;
                break;
              }
            if(already_for_sharing)
              retval = lockStatus::WAITING;                                 
            else
            {
              lr->setLockStatus(lockStatus::WAITING);
              lock_table[resource_name]->emplace_back(lr);
              retval = lockStatus::WAITING;                                 
            }
          }
          else
          {
            lr->setLockStatus(lockStatus::GRANTED);
            lock_table[resource_name]->emplace_back(lr);
            retval = lockStatus::GRANTED;                          
          }
        }

        // txnid waiting for SHARED and asked for EXCLUSIVE
        else
        {
          (*findIter_waiting)->setLockType(lockType::EXCLUSIVE);
          retval = (*findIter_waiting)->getLockStatus();         
        }
      }
    }
  }
  return retval;
}

uint8_t unlock(std::string resource_name,
               std::uint32_t txn_id)
{
  std::cout << "request from txn_id " << txn_id << " for unlocking resource " << resource_name << "...\n";
  uint8_t retval = true;

  if(lock_table.find(resource_name) != lock_table.end())
  {
    std::list<lockable_resource*>::iterator iter = lock_table[resource_name]->begin();
    for( ; iter != lock_table[resource_name]->end(); iter++)
    {
      if((*iter)->getTxnId() == txn_id)
      {
        if((*iter)->getLockStatus() == lockStatus::WAITING)
        {
          std::cout << "cannot be unlocked as txnId " << txn_id << " is not holding the lock\n";
          retval = false;
          return retval; 
        }
        uint8_t lock_type = (*iter)->getLockType();
        std::list<lockable_resource*>::iterator it = iter;
        it++;
        lock_table[resource_name]->erase(iter);
        bool shared = false;
        // list lock_table[resource_name] is not empty
        if(!lock_table[resource_name]->empty())
        {
          // released lock was EXCLUSIVE
          if(lock_type == lockType::EXCLUSIVE)
          {
            (*it)->setLockStatus(lockStatus::GRANTED);
            std::cout << (*it)->getLockType() << " lock being GRANTED for txnId " << (*it)->getTxnId() << " on resource AAA" << std::endl;
            if((*it)->getLockType() == lockType::SHARED)
            {
              std::cout << " SHARED lock being GRANTED for txnId " << (*it)->getTxnId() << " on resource AAA" << std::endl;
              std::list<lockable_resource*>::iterator tmp_it = it;
              tmp_it++;
              for( ; tmp_it != lock_table[resource_name]->end(); tmp_it++)
              {
                if((*tmp_it)->getLockType() == lockType::SHARED && (*tmp_it)->getLockStatus() != lockStatus::GRANTED)
                {
                  (*tmp_it)->setLockStatus(lockStatus::GRANTED);
                  std::cout << "SHARED lock being GRANTED for txnId " << (*tmp_it)->getTxnId() << " on resource AAA" << std::endl;
                }
              }
            }
          }

          // released lock was SHARED
          else
          {
            // released lock was SHARED and next lock is also SHARED
            if((*it)->getLockType() == lockType::SHARED)
            {
              std::list<lockable_resource*>::iterator tmp_it = it;
              for( ; tmp_it != lock_table[resource_name]->end(); tmp_it++)
              {
                // if request is SHARED, then request GRANTED
                if((*tmp_it)->getLockType() == lockType::SHARED && (*tmp_it)->getLockStatus() != lockStatus::GRANTED)
                {
                  (*tmp_it)->setLockStatus(lockStatus::GRANTED);                  
                  std::cout << "SHARED lock being GRANTED for txnId " << (*tmp_it)->getTxnId() << " on resource AAA" << std::endl;
                }
              }
            }

            // released lock was SHARED and next lock is EXCLUSIVE
            else
            {
              std::list<lockable_resource*>::iterator tmp_it = it;
              // checking for an SHARED lock
              for( ; tmp_it != lock_table[resource_name]->end(); tmp_it++)
              {
                if((*tmp_it)->getLockType() == lockType::SHARED)
                {
                  shared = true;
                  break;
                }
              }

              // released lock was SHARED and NO SHARED lock after that 
              if(!shared)
              {
                (*it)->setLockStatus(lockStatus::GRANTED);
                std::cout << "lock GRANTED for txnId " << (*it)->getTxnId() << " on resource AAA" << std::endl;
              }
            }
          }
        }

        // list lock_table[resource_name] is empty
        else
        {
          lock_table.erase(resource_name);
        }
        break;
      }
    }
  }
  else
  {
    std::cerr<<"ERROR: no such resource is found."<<endl;
    return false;
  }
  return retval;
}

void printList(std::string resource_name)
{
  std::cout << "\n-------------------------- resource_name: " << resource_name << " --------------------------";
  if(lock_table.find(resource_name) == lock_table.end())
  {
    std::cout << "No lock GRANTED or WAITING for resource " << resource_name << "\n";
  }
  else
  {
    std::list<lockable_resource*>::iterator iter = lock_table[resource_name]->begin();
    std::cout << "\n";
    for( ; iter != lock_table[resource_name]->end(); iter++)
    {
      std::cout << "TxnId: " << (*iter)->getTxnId() << "\t\t\t";
      if((*iter)->getLockType() == lockType::SHARED)
        std::cout << "SHARED\t\t\t\t";
      else
        std::cout << "EXCLUSIVE\t\t\t";
      if((*iter)->getLockStatus() == lockStatus::GRANTED)
        std::cout << "GRANTED\n";
      else
        std::cout << "WAITING\n";
    }
  }
  std::cout << "------------------------------------------------------------------------\n\n";

}
