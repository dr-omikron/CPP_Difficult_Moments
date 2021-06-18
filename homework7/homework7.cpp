
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <numeric>
#include "students.pb.h"


class FullName {
	std::string _surname;
	std::string _name;
	std::string _patronymic;
public:
	FullName(){}
	FullName(std::string surname, std::string name, std::string patronymic)
		: _surname(surname), _name(name), _patronymic(patronymic) { }
	FullName(const serialization::FullName& sfn) {
		_surname = sfn.surname();
		_name = sfn.name();
		_patronymic = sfn.patronymic();
	}
	void ConvertToSerializationType(serialization::FullName* sfn) {
		sfn->set_name(_name);
		sfn->set_surname(_surname);
		sfn->set_patronymic(_patronymic);
	}
	friend bool operator==(const FullName& lhs, const FullName& rhs) {
		return lhs._surname == lhs._surname && lhs._name == rhs._name && rhs._patronymic == rhs._patronymic;
	}
	friend std::ostream& operator<<(std::ostream& out, const FullName& sfn) {
		out << sfn._surname << " " << sfn._name << " " << sfn._patronymic;
		return out;
	}
};

class Student {
	FullName _full_name;
	std::vector<int> _grades;
	int _average_grade;
public:
	Student(const FullName& full_name, std::vector<int> grades, int average_grade)
		: _full_name(full_name), _grades(grades), _average_grade(average_grade) { }
	Student(const serialization::Student& st) {
		_average_grade = st.averagegrade();
		for (size_t i = 0; i < st.grades_size(); ++i) {
			_grades.push_back(st.grades(i));
		}
		_full_name = FullName(st.fullname());
	}

	void ConvertToSerializationType(serialization::Student* st) {
		for_each(_grades.begin(), _grades.end(), [&st](int value) { st->add_grades(value); });
		st->set_averagegrade(_average_grade);
		serialization::FullName* fn = st->mutable_fullname();
		_full_name.ConvertToSerializationType(fn);
	}

	friend std::ostream& operator<<(std::ostream& out, const Student& st) {
		out << st._full_name << " ";
		copy(st._grades.begin(), st._grades.end(), std::ostream_iterator<int>(out, " "));
		return out;
	}

	const FullName& GetFullName() const { return _full_name; }
	const std::vector<int>& GetGrades() const { return _grades; }
};

class IRepository {
	virtual void Open() = 0; 
	virtual void Save() = 0;
};

class IMethods {
	virtual int GetAverageScore(const FullName& name) = 0;
	virtual std::string GetAllInfo(const FullName& name) = 0;
	virtual std::string GetAllInfo() = 0;
};

class StudentsGroup : public IRepository, public IMethods {
private:
	std::vector<Student> _students;
	serialization::StudentsGroup ConvertToSerializationType(std::vector<Student> students) {
		serialization::StudentsGroup sg;
		for (auto student : students) {
			serialization::Student* st = sg.add_students();
			student.ConvertToSerializationType(st);
		}
		return sg;
	}
	std::vector<Student> ConvertFromSerializationType(serialization::StudentsGroup students) {
		std::vector<Student> sg;
		for (size_t i = 0; i < students.students_size(); i++) {
			serialization::Student st = students.students(i);
			sg.push_back(Student(students.students(i)));
		}
		return sg;
	}
public:
	StudentsGroup() { }
	StudentsGroup(std::vector<Student> students)
		: _students(students) { }
	void Open() override {
		serialization::StudentsGroup s;
		std::ifstream in("students.bin", std::ios_base::binary);
		_students = ConvertFromSerializationType(s);
	}
	void Save() override {

		serialization::StudentsGroup s = ConvertToSerializationType(_students);
		std::ofstream out("students.bin", std::ios_base::binary);
		s.SerializeToOstream(&out);
	}

	friend std::ostream& operator<<(std::ostream& out, const StudentsGroup& sg) {
		copy(sg._students.begin(), sg._students.end(), std::ostream_iterator<Student>(out, "\n"));
		return out;
	}

	int GetAverageScore(const FullName& name) override {
		auto finded = std::find_if(_students.begin(), _students.end(), [&](const Student& st) {return name == st.GetFullName(); });
		if (finded != _students.end()) {
			auto grades = finded->GetGrades();
			return std::accumulate(grades.begin(), grades.end(), 0) / grades.size();
		}
		return 0;
	}
	std::string GetAllInfo(const FullName& name) override {
		auto finded = std::find_if(_students.begin(), _students.end(), [&](const Student& st) {return name == st.GetFullName(); });
		if (finded != _students.end()) {
			std::ostringstream ss;
			ss << *finded;
			return ss.str();
		}
		return std::string();
	}
	std::string GetAllInfo() override {
		std::ostringstream ss;
		ss << *this;
		return ss.str();
	}
};



int main()
{
	StudentsGroup group1(std::vector<Student> {
			Student({ "Semina", "Ekaterina", "Vladimirovna" }, { 7, 2, 8, 6, 9 }, 6),
			Student({ "Trofimova", "Elena", "Sergeevna" }, { 8, 9, 5, 6, 10 }, 7),
			Student({ "Rodionov", "Aleksey", "Ivanovich" }, { 9, 8, 7, 9, 8 }, 8)
	});
	group1.Save();
	StudentsGroup group2;
	group2.Open();
	std::cout << group2.GetAverageScore(FullName("Trofimova", "Elena", "Sergeevna")) << std::endl;
	std::cout << group2.GetAllInfo(FullName("Rodionov", "Aleksey", "Ivanovich")) << std::endl;
	std::cout << group2.GetAllInfo() << std::endl;

}
