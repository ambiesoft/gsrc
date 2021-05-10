#include <thread>
// https://www.suninf.net/2013/12/thread-and-messageloop-in-chrome.html

#include "base/bind.h"
#include "base/memory/weak_ptr.h"
#include "base/threading/thread.h"

struct DataBuffer : base::RefCountedThreadSafe<DataBuffer> {
 private:
  friend class base::RefCountedThreadSafe<DataBuffer>;
  ~DataBuffer() {}

 public:
  std::string data_;
};

class ThreadTest : public base::RefCountedThreadSafe<ThreadTest> {
 private:
  friend class base::RefCountedThreadSafe<ThreadTest>;
  ~ThreadTest() {}

 public:
  ThreadTest() : worker_thread_("worker") {
    base::Thread::Options options;
    options.message_loop_type = base::MessageLoop::TYPE_DEFAULT;
    worker_thread_.StartWithOptions(options);
  }

  void work() {
    scoped_refptr<DataBuffer> buf = new DataBuffer;

    // PostTaskAndReply need to be called on thread with a base::MessageLoop
    worker_thread_.task_runner()->PostTaskAndReply(
        FROM_HERE,
        base::Bind(&ThreadTest::DoTask, scoped_refptr<ThreadTest>(this), buf),
        base::Bind(&ThreadTest::OnReply, scoped_refptr<ThreadTest>(this), buf));
  }

 private:
  void DoTask(scoped_refptr<DataBuffer> buf) {
    // Prepare data
    if (buf) {
      buf->data_ = "hello";
    }
  }

  void OnReply(scoped_refptr<DataBuffer> buf) {
    // Deal with data
    DCHECK(buf->data_ == "hello");
  }

 private:
  base::Thread worker_thread_;
};

// global
scoped_refptr<ThreadTest> g_test;

void ThreadTestFunc() {
  g_test = new ThreadTest;
  g_test->work();
}

int main() {
  ThreadTestFunc();

  // wait for very long time
  std::this_thread::sleep_for(std::chrono::hours::max());
}
