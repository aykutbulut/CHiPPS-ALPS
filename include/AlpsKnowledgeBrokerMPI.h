#include "AlpsLicense.h"

#ifndef AlpsKnowledgeBrokerMPI_h_
#define AlpsKnowledgeBrokerMPI_h_

//#include "/usr/include/mpi.h"
//#include "/usr/mpi/mpich-1.2.3-3/include/mpi.h"
#include "mpi.h"

#include "AlpsEnumProcessT.h"
#include "AlpsKnowledge.h"
#include "AlpsKnowledgeBroker.h"

//#############################################################################

class AlpsKnowledgeBrokerMPI : public AlpsKnowledgeBroker {
 private:
  AlpsKnowledgeBrokerMPI(const AlpsKnowledgeBrokerMPI&);
  AlpsKnowledgeBrokerMPI& operator=(const AlpsKnowledgeBrokerMPI&);
 
  /** Buffer used to send or receive messages. */
  char* buf_;
  /** Size of buf_.*/
  int size_;
  /** Used in MPI_Pack and MPI_Unpack to record current pos in buffer. */
  int position_;

 public:
  AlpsKnowledgeBrokerMPI()
    : 
    AlpsKnowledgeBroker(new AlpsSubTreeMaster),
    buf_(0),
    position_(0)
    {}
   
  ~AlpsKnowledgeBrokerMPI() {}

  /** @name Message passing functions
   *
   */
  //@{
  /** Pack the representation of enc into buf_. */
  void pack(AlpsEncoded* enc);
 
  /** Unpack buf_ into an enc. */
  AlpsEncoded* unpack();
  
  /** Receive message and put it into buf_. */
  void receive(int sender, int tag, MPI_Comm comm, MPI_Status* status);

  /** Send the packed message in buf_ to target. */
  void send(const int target, const int tag, MPI_Comm comm);

  /** Initialize message environment. */
  void initMsgEnv(int argc, char* argv[], 
		  int& myRank, int& procSize, const int comm = 91);

  /** Finalize the message environment. */
  void finializeMsgEnv();
  //@}

  void exploreSubTree(AlpsTreeNode* root, 
		      const int id,
		      int comm = 91 /*MPI_COMM_WORLD=91*/ );
};

#endif
//#############################################################################
