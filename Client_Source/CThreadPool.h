#pragma once
class ThreadPool {
public:
	ThreadPool(size_t num_threads);
	~ThreadPool();

	// job �� �߰��Ѵ�.
	void EnqueueJob(std::function<void()> job);

private:
	// �� Worker �������� ����.
	size_t num_threads_;
	// Worker �����带 �����ϴ� ����.
	std::vector<std::thread> worker_threads_;
	// ���ϵ��� �����ϴ� job ť.
	std::queue<std::function<void()>> jobs_;
	// ���� job ť�� ���� cv �� m.
	std::condition_variable cv_job_q_;
	std::mutex m_job_q_;

	// ��� ������ ����
	bool stop_all;

	// Worker ������
	void WorkerThread();
};



