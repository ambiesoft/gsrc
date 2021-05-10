// src/components/frob/frobinator_impl.cc

#include "base/task/single_thread_task_executor.h"

#include "mojo/public/cpp/bindings/binding.h"
#include "mojo/public/cpp/bindings/interface_request.h"
#include "mojo/public/cpp/bindings/remote.h"

#include "mojo/core/embedder/scoped_ipc_support.h"
#include "mojo/core/embedder/embedder.h"

#include "mysrc/my_frob/public/mojom/frobinator.mojom.h"

namespace frob {

class FrobinatorImpl : public mojom::Frobinator {
 public:
  FrobinatorImpl(mojom::FrobinatorRequest request)
      : binding_(this, std::move(request)) {}
  ~FrobinatorImpl() override {}

  // mojom::Frobinator:
  void Frobinate() override { DLOG(INFO) << "I can't stop frobinating!"; }

 private:
  mojo::Binding<mojom::Frobinator> binding_;
};

}  // namespace frob

int main() {
  mojo::core::Init();

    
  base::SingleThreadTaskExecutor main_task_executor(base::MessagePumpType::IO);
  // base::TestIOThread test_io_thread(base::TestIOThread::kAutoStart);

  mojo::core::ScopedIPCSupport ipc_support(
      main_task_executor.task_runner(),
      mojo::core::ScopedIPCSupport::ShutdownPolicy::CLEAN);

  mojo::Remote<frob::mojom::Frobinator> frobinator;
  auto receiver = frobinator.BindNewPipeAndPassReceiver();

  //FrobinatorPtr frobinator;
  //mojom::FrobinatorRequest request = mojo::GetProxy(&frobinator);
  //frob::FrobinatorImpl impl(request);

  //// Tada!
  //frobinator->Frobinate();
  return 0;
}