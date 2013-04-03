#ifndef __TASK_H
#define __TASK_H

#include <string>
#include <fstream>

#include <boost/serialization/access.hpp>


enum Priority {
	LOW,
	NORMAL,
	HIGH,
	LAST_PRIO
};

enum Status {
	NEW,
	IN_PROGRESS,
	COMPLETE,
	LAST_STATUS
};


class Task {
	friend class boost::serialization::access;

	public:
		static const char* prio[LAST_PRIO];
		static const char* stat[LAST_STATUS];

		Task();
		Task(const std::string& theDescription, Priority thePriority = NORMAL, Status theStatus = NEW);
		bool operator==(const Task& theTask) const;
		bool operator<(const Task& theTask) const;

		const std::string toString() const;

		const std::string& getDescription() const;
		const Priority getPriority() const;
		const Status getStatus() const;

		void setIdx(int theIdx);
		void setDescription(const std::string theDescription);
		void setPriority(Priority thePriority);
		void setStatus(Status theStatus);

	private:
		mutable int idx;
		std::string description;
		Priority priority;
		Status status;

		template<class Archive>
			void serialize(Archive& ar, const unsigned int version) {
				ar & status;
				ar & priority;
				ar & description;
			}
};

//--getters
inline const std::string& Task::getDescription() const {
	return description;
}

inline const Priority Task::getPriority() const {
	return priority;
}

inline const Status Task::getStatus() const {
	return status;
}

//--setters
inline void Task::setIdx(int theIdx) {
	idx = theIdx;
}

inline void Task::setDescription(const std::string theDescription) {
	description = theDescription;
}

inline void Task::setPriority(Priority thePriority) {
	priority = thePriority;
}

inline void Task::setStatus(Status theStatus) {
	status = theStatus;
}

//--operators
inline bool Task::operator==(const Task& theTask) const {
	return description == theTask.description;
}

#endif //__TASK_H

