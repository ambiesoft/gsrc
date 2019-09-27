#include "base/process/process_handle.h"
#include "base/threading/thread.h"
#include "mojo/core/embedder/embedder.h"
#include "mojo/core/embedder/outgoing_broker_client_invitation.h"
#include "mojo/core/embedder/platform_channel_pair.h"
#include "mojo/core/embedder/scoped_ipc_support.h"

// You write this. It launches a new process, passing the pipe handle
// encapsulated by |channel| by any means possible (e.g. on Windows or POSIX
// you may inhert the file descriptor/HANDLE at launch and pass a commandline
// argument to indicate its numeric value). Returns the handle of the new
// process.
base::ProcessHandle LaunchCoolChildProcess(
    mojo::core::ScopedPlatformHandle channel);

int main(int argc, char** argv) {
  mojo::core::Init();

  base::Thread ipc_thread("ipc!");
  ipc_thread.StartWithOptions(
      base::Thread::Options(base::MessageLoop::TYPE_IO, 0));

  mojo::core::ScopedIPCSupport ipc_support(
      ipc_thread.task_runner(),
      mojo::core::ScopedIPCSupport::ShutdownPolicy::CLEAN);

  // This is essentially always an OS pipe (domain socket pair, Windows named
  // pipe, etc.)
  mojo::core::PlatformChannelPair channel;

  // This is a scoper which encapsulates the intent to connect to another
  // process. It exists because process connection is inherently asynchronous,
  // things may go wrong, and the lifetime of any associated resources is bound
  // by the lifetime of this object regardless of success or failure.
  mojo::core::OutgoingBrokerClientInvitation invitation;

  base::ProcessHandle child_handle =
      LaunchCoolChildProcess(channel.PassClientHandle());

  // At this point it's safe for |child| to go out of scope and nothing will
  // break.
  child.Connect(child_handle, channel.PassServerHandle());

  return 0;
}