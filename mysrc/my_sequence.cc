#include "base/sequenced_task_runner.h"
#include "base/task/post_task.h"
#include "base/run_loop.h"
#include "base/message_loop/message_loop.h"


class A {
 public:
  A() {
    // アクセスは作成シーケンス上にあることを要求しない。
    DETACH_FROM_SEQUENCE(sequence_checker_);
  }

  void AddValue(int v) {
    // すべてのアクセスが同じシーケンスかをチェック。
    DCHECK_CALLED_ON_VALID_SEQUENCE(sequence_checker_);
    values_.push_back(v);
  }

 private:
  SEQUENCE_CHECKER(sequence_checker_);

  // すべてのアクセスは同じシーケンス上にあるので
  // ロックは必要ない。
  std::vector<int> values_;
};

int main() {
  A a;
  base::MessageLoop main_loop;
  base::RunLoop run_loop;
  
  //scoped_refptr<SequencedTaskRunner> task_runner_for_a =
  //    base::CreateSequencedTaskRunnerWithTraits({base::ThreadPool()});
  scoped_refptr<base::SequencedTaskRunner> task_runner_for_a =
	  base::CreateSequencedTaskRunnerWithTraits({
	  base::MayBlock(), base::TaskPriority::BEST_EFFORT});

  task_runner_for_a->PostTask(
      FROM_HERE, base::BindOnce(&A::AddValue, base::Unretained(&a), 42));
  task_runner_for_a->PostTask(
      FROM_HERE, base::BindOnce(&A::AddValue, base::Unretained(&a), 27));

  // 違うシーケンスからのアクセスはDCHECKで失敗する。
  scoped_refptr<base::SequencedTaskRunner> other_task_runner =
      base::CreateSequencedTaskRunnerWithTraits({base::ThreadPool()});
  other_task_runner->PostTask(
      FROM_HERE, base::BindOnce(&A::AddValue, base::Unretained(&a), 1));

  main_loop.task_runner()->PostDelayedTask(
      FROM_HERE, run_loop.QuitClosure(),
      base::TimeDelta::FromMicroseconds(1000));

  run_loop.Run();
  return 0;
}