#include "mysrc/my_mojo_db/db.mojom.h"

#include "base/task/post_task.h"
#include "base/task/task_traits.h"
#include "base/task/single_thread_task_executor.h"
#include "base/run_loop.h"

#include "mojo/core/embedder/embedder.h"
#include "mojo/core/embedder/scoped_ipc_support.h"
#include "mojo/public/cpp/bindings/pending_receiver.h"
#include "mojo/public/cpp/bindings/pending_remote.h"
#include "mojo/public/cpp/bindings/receiver.h"
#include "mojo/public/cpp/bindings/remote.h"


class TableImpl : public db::mojom::Table {
 public:
  // NOTE: A common pattern for interface implementations which have one
  // instance per client is to take a PendingReceiver in the constructor.

  explicit TableImpl(mojo::PendingReceiver<db::mojom::Table> receiver)
      : receiver_(this, std::move(receiver)) {}
  ~TableImpl() override {}

  // db::mojom::Table
  void AddRow(int32_t key, const std::string& data) override {
    LOG(ERROR) << "[AddRow] " << data;
  }

 private:
  mojo::Receiver<db::mojom::Table> receiver_;

  DISALLOW_COPY_AND_ASSIGN(TableImpl);
};


int main()
{
  mojo::core::Init();
  //scoped_refptr<base::SequencedTaskRunner> task_runner =
  //    CreateSequencedTaskRunner({ThreadPool()});
  base::SingleThreadTaskExecutor main_task_executor(base::MessagePumpType::IO);


  // method 1 verbose
  //mojo::MessagePipe pipe;
  //mojo::Remote<db::mojom::Table> table(
  //  mojo::PendingRemote<db::mojom::Table>(std::move(pipe.handle0), 0));

  //mojo::PendingReceiver<db::mojom::Table> receiver(std::move(pipe.handle1));

  // method 2
  mojo::Remote<db::mojom::Table> table;
  auto receiver = table.BindNewPipeAndPassReceiver();
  TableImpl impl(std::move(receiver));

  // operator-> returns proxy, proxy inherits Table
  table->AddRow(22, "aaa");


  // Process all tasks
  base::RunLoop runLoop;
  runLoop.QuitWhenIdle();
  runLoop.Run();

  return 0;
}