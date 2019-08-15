#include <iostream>
#include <map>
#include <vector>

using namespace std;

// Перечислимый тип для статуса задачи
enum class TaskStatus {
    NEW,          // новая
    IN_PROGRESS,  // в разработке
    TESTING,      // на тестировании
    DONE          // завершена
};


// Объявляем тип-синоним для map<TaskStatus, int>,
// позволяющего хранить количество задач каждого статуса
using TasksInfo = map<TaskStatus, int>;

const vector<TaskStatus> task_status_sequence = {TaskStatus::NEW,
                                                 TaskStatus::IN_PROGRESS,
                                                 TaskStatus::TESTING,
                                                 TaskStatus::DONE};
class TeamTasks {
private:
    map<string, TasksInfo> person_tasks;
public:
    // Получить статистику по статусам задач конкретного разработчика
    const TasksInfo &GetPersonTasksInfo(const string &person) const {
        return person_tasks.at(person);
    };

    // Добавить новую задачу (в статусе NEW) для конкретного разработчитка
    void AddNewTask(const string &person) {
        try {
            person_tasks.at(person)[TaskStatus::NEW] += 1;
        }
        catch (const out_of_range &e) {
            person_tasks[person] = {{TaskStatus::NEW,         1},
                                    {TaskStatus::IN_PROGRESS, 0},
                                    {TaskStatus::TESTING,     0},
                                    {TaskStatus::DONE,        0}};
        }
    };

    // Обновить статусы по данному количеству задач конкретного разработчика,
    // подробности см. ниже
    tuple<TasksInfo, TasksInfo> PerformPersonTasks(
            const string &person, int task_count) {
        TasksInfo updated_tasks;
        TasksInfo unchanged_tasks;
        int update_tasks = 0;
        /* 4 -> 3 2 4 1 */
        for (auto i = cbegin(task_status_sequence); *i != TaskStatus::DONE; ++i) {
            update_tasks = min(person_tasks[person][*i], task_count);
            task_count -= update_tasks;

            if (update_tasks) { // person has tasks of this type and task_count
                updated_tasks[*(i + 1)] = update_tasks;
                person_tasks[person][*i] -= update_tasks;
            }

            if (person_tasks[person][*i]) { // person still has tasks of this type
                unchanged_tasks[*i] = person_tasks[person][*i];
            }
        }
        for (const auto &t: updated_tasks) {
            person_tasks[person][t.first] += t.second;
        };
        return {updated_tasks, unchanged_tasks};
    };
};

// Принимаем словарь по значению, чтобы иметь возможность
// обращаться к отсутствующим ключам с помощью [] и получать 0,
// не меняя при этом исходный словарь
void PrintTasksInfo(TasksInfo tasks_info) {
    cout << tasks_info[TaskStatus::NEW] << " new tasks" <<
         ", " << tasks_info[TaskStatus::IN_PROGRESS] << " tasks in progress" <<
         ", " << tasks_info[TaskStatus::TESTING] << " tasks are being tested" <<
         ", " << tasks_info[TaskStatus::DONE] << " tasks are done" << endl;
}

int main() {
    TeamTasks tasks;
    tasks.AddNewTask("Ilia");
    for (int i = 0; i < 3; ++i) {
        tasks.AddNewTask("Ivan");
    }
    cout << "Ilia's tasks: ";
    PrintTasksInfo(tasks.GetPersonTasksInfo("Ilia"));
    cout << "Ivan's tasks: ";
    PrintTasksInfo(tasks.GetPersonTasksInfo("Ivan"));

    TasksInfo updated_tasks, untouched_tasks;

    tie(updated_tasks, untouched_tasks) =
            tasks.PerformPersonTasks("Ivan", 2);
    cout << "Updated Ivan's tasks: ";
    PrintTasksInfo(updated_tasks);
    cout << "Untouched Ivan's tasks: ";
    PrintTasksInfo(untouched_tasks);

    tie(updated_tasks, untouched_tasks) =
            tasks.PerformPersonTasks("Ivan", 2);
    cout << "Updated Ivan's tasks: ";
    PrintTasksInfo(updated_tasks);
    cout << "Untouched Ivan's tasks: ";
    PrintTasksInfo(untouched_tasks);

    return 0;
}