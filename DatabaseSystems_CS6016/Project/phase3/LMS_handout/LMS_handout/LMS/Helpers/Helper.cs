using System;
using LMS.Models.LMSModels;
using System.Linq;
using System.Collections.Generic;

namespace LMS.Helpers
{
    public class Helper
    {
        public Helper()
        {
        }

        public void UpdateGrade(string grade, string uid, string subject, int num, string season, int year)
        {
            using (var context = new Team12LMSContext())
            {
                var sid = from s in context.Students
                          where s.UId == uid
                          select s.StudentId;

                var cid = from c in context.Courses
                          where c.Dept == subject && c.Number == num.ToString()
                          join cl in context.Classes
                          on c.CatalogId equals cl.CatalogId
                          into join1
                          from j1 in join1
                          where j1.Semester == season + year.ToString()
                          select j1.ClassId;

                var dep = from d in context.Enrollments
                          where d.Class == cid.First() && d.Student == sid.First()
                          select d;

                dep.First().Grade = grade;
                context.SaveChanges();
            }



        }

        public String CalculateGrade(string subject, int num, string season, int year, string uid)
        {
            var grade = 0.0;

            using (var context = new Team12LMSContext())
            {
                var ac = from c in context.Courses
                         where c.Dept == subject && c.Number == num.ToString()
                         join cl in context.Classes
                         on c.CatalogId equals cl.CatalogId
                         into join1
                         from j1 in join1
                         where j1.Semester == season + year.ToString()
                         join asc in context.AssignmentCategories
                         on j1.ClassId equals asc.ClassId
                         into join2
                         from j2 in join2
                         select j2;

                var total = 0;

                foreach (var cat in ac)
                {
                    total += cat.GradingWeight;
                }

                var scalar = 100/total;

                var sid = from s in context.Students
                          where s.UId == uid
                          select s.StudentId;


                foreach (var c in ac)
                {

                    var acs = from assc in context.AssignmentCategories
                            where assc.CategoryId == c.CategoryId
                            join a in context.Assignments
                            on assc.CategoryId equals a.Category
                            into join1
                            from j1 in join1
                            join s in context.Submissions
                            on j1.AssignmentId equals s.Assignment
                            into join2
                            from j2 in join2
                            where j2.Student == sid.First()
                            select new { earned = j2.Score==null? 0: j2.Score.Value, points = j1.MaxPointVal };

                    int earned = 0;

                    var max = 0;


                    foreach (var s in acs)
                    {
                        
                        earned += s.earned;
                        max += s.points;
                    }

                    grade += Convert.ToDouble(earned) / Convert.ToDouble(max) * c.GradingWeight;
                }
                grade /= total;


            }
            var map = new Dictionary<Func<double, bool>, String>()
            {
                    {d => d <= 1.0 && d >= 0.93, "A" },
                    {d => d < 0.93 && d >= 0.90, "A-" },
                    {d => d < 0.90 && d >= 0.87, "B+" },
                    {d => d < 0.87 && d >= 0.83, "B" },
                    {d => d < 0.83 && d >= 0.80, "B-" },
                    {d => d < 0.80 && d >= 0.77, "C+" },
                    {d => d < 0.77 && d >= 0.73, "C" },
                    {d => d < 0.73 && d >= 0.70, "C-" },
                    {d => d < 0.70 && d >= 0.67, "D+" },
                    {d => d < 0.67 && d >= 0.63, "D" },
                    {d => d < 0.63 && d >= 0.60, "D-" },
                    {d => d < .60, "F" }
            };

            var key = map.Keys.Single(g => g(grade));
            return(map[key]);
        }
    }
}
