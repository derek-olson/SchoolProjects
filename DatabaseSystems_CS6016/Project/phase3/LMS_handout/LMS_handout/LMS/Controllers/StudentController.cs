using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Threading.Tasks;
using LMS.Models.LMSModels;
using Microsoft.AspNetCore.Authorization;
using Microsoft.AspNetCore.Mvc;

namespace LMS.Controllers
{
    [Authorize(Roles = "Student")]
    public class StudentController : CommonController
    {

        public IActionResult Index()
        {
            return View();
        }

        public IActionResult Catalog()
        {
            return View();
        }

        public IActionResult Class(string subject, string num, string season, string year)
        {
            ViewData["subject"] = subject;
            ViewData["num"] = num;
            ViewData["season"] = season;
            ViewData["year"] = year;
            return View();
        }

        public IActionResult Assignment(string subject, string num, string season, string year, string cat, string aname)
        {
            ViewData["subject"] = subject;
            ViewData["num"] = num;
            ViewData["season"] = season;
            ViewData["year"] = year;
            ViewData["cat"] = cat;
            ViewData["aname"] = aname;
            return View();
        }


        public IActionResult ClassListings(string subject, string num)
        {
            System.Diagnostics.Debug.WriteLine(subject + num);
            ViewData["subject"] = subject;
            ViewData["num"] = num;
            return View();
        }


        /*******Begin code to modify********/

        /// <summary>
        /// Returns a JSON array of the classes the given student is enrolled in.
        /// Each object in the array should have the following fields:
        /// "subject" - The subject abbreviation of the class (such as "CS")
        /// "number" - The course number (such as 5530)
        /// "name" - The course name
        /// "season" - The season part of the semester
        /// "year" - The year part of the semester
        /// "grade" - The grade earned in the class, or "--" if one hasn't been assigned
        /// </summary>
        /// <param name="uid">The uid of the student</param>
        /// <returns>The JSON array</returns>
        public IActionResult GetMyClasses(string uid)
        {
            var query = from s in db.Students
                        where s.UId == uid
                        join e in db.Enrollments
                        on s.StudentId equals e.Student
                        into join1
                        from j1 in join1
                        join c in db.Classes
                        on j1.Class equals c.ClassId
                        into join2
                        from j2 in join2
                        join cr in db.Courses
                        on j2.CatalogId equals cr.CatalogId
                        into join3
                        from j3 in join3
                        select new { subject = j3.Dept, j3.Number, j3.Name, season = j2.Semester.Substring(0, j2.Semester.Length - 4), year = j2.Semester.Substring(j2.Semester.Length - 4, 4), j1.Grade };

            return Json(query.ToArray());
        }

        /// <summary>
        /// Returns a JSON array of all the assignments in the given class that the given student is enrolled in.
        /// Each object in the array should have the following fields:
        /// "aname" - The assignment name
        /// "cname" - The category name that the assignment belongs to
        /// "due" - The due Date/Time
        /// "score" - The score earned by the student, or null if the student has not submitted to this assignment.
        /// </summary>
        /// <param name="subject">The course subject abbreviation</param>
        /// <param name="num">The course number</param>
        /// <param name="season">The season part of the semester for the class the assignment belongs to</param>
        /// <param name="year">The year part of the semester for the class the assignment belongs to</param>
        /// <param name="uid"></param>
        /// <returns>The JSON array</returns>
        public IActionResult GetAssignmentsInClass(string subject, int num, string season, int year, string uid)
        {
            var query = from c in db.Courses
                        where c.Dept == subject && c.Number == num.ToString()
                        join cl in db.Classes
                        on c.CatalogId equals cl.CatalogId
                        into jn
                        from j in jn
                        where j.Semester == season + year.ToString()
                        select j.ClassId;

            var q2 = from s in db.Students
                     where s.UId == uid
                     join e in db.Enrollments
                     on s.StudentId equals e.Student
                     into join1
                     from j1 in join1
                     join c in db.Classes
                     on j1.Class equals c.ClassId
                     into join2
                     from j2 in join2
                     where j2.ClassId == query.First()
                     join ac in db.AssignmentCategories
                     on j2.ClassId equals ac.ClassId
                     into join3
                     from j3 in join3
                     join a in db.Assignments
                     on j3.CategoryId equals a.Category
                     into join4
                     from j4 in join4

                     select new { aname = j4.Name, cname = j3.Name, due = j4.DueDate, score = from j04 in join4 where j04.AssignmentId == j4.AssignmentId join sub in db.Submissions on j04.AssignmentId equals sub.Assignment into join5 from j5 in join5 where j1.Student == j5.Student select j5.Score};


            return Json(q2.ToArray());
        }



        /// <summary>
        /// Adds a submission to the given assignment for the given student
        /// The submission should use the current time as its DateTime
        /// You can get the current time with DateTime.Now
        /// The score of the submission should start as 0 until a Professor grades it
        /// If a Student submits to an assignment again, it should replace the submission contents
        /// and the submission time (the score should remain the same).
        /// </summary>
        /// <param name="subject">The course subject abbreviation</param>
        /// <param name="num">The course number</param>
        /// <param name="season">The season part of the semester for the class the assignment belongs to</param>
        /// <param name="year">The year part of the semester for the class the assignment belongs to</param>
        /// <param name="category">The name of the assignment category in the class</param>
        /// <param name="asgname">The new assignment name</param>
        /// <param name="uid">The student submitting the assignment</param>
        /// <param name="contents">The text contents of the student's submission</param>
        /// <returns>A JSON object containing {success = true/false}</returns>
        public IActionResult SubmitAssignmentText(string subject, int num, string season, int year,
          string category, string asgname, string uid, string contents)
        {
            var getIds = from s in db.Submissions
                         select s.SubmissionId;

            var max = getIds.Max();

            var sid = from s in db.Students
                      where s.UId == uid
                      select s.StudentId;

            var aid = from c in db.Courses
                      where c.Dept == subject && c.Number == num.ToString()
                      join cl in db.Classes
                      on c.CatalogId equals cl.CatalogId
                      into join1
                      from j1 in join1
                      where j1.Semester == season + year.ToString()
                      join ac in db.AssignmentCategories
                      on j1.ClassId equals ac.ClassId
                      into join2
                      from j2 in join2
                      where j2.Name == category
                      join a in db.Assignments 
                      on j2.CategoryId equals a.Category
                      into join3
                      from j3 in join3
                      where j3.Name == asgname
                      select j3.AssignmentId;

            Submissions submission = new Submissions();
            submission.Assignment = aid.First();
            submission.Student = sid.First();
            submission.Contents = contents;
            submission.Time = DateTime.UtcNow;

            var subID = max + 1;
            submission.SubmissionId = subID;
            submission.Score = null;

            try
            {
                db.Submissions.Add(submission);
                db.SaveChanges();
            }
            catch(Exception ex)
            {
                Debug.Write(ex);
                return Json(new { success = false });
            }
            return Json(new { success = true });
        }


        /// <summary>
        /// Enrolls a student in a class.
        /// </summary>
        /// <param name="subject">The department subject abbreviation</param>
        /// <param name="num">The course number</param>
        /// <param name="season">The season part of the semester</param>
        /// <param name="year">The year part of the semester</param>
        /// <param name="uid">The uid of the student</param>
        /// <returns>A JSON object containing {success = {true/false}. 
        /// false if the student is already enrolled in the class, true otherwise.</returns>
        public IActionResult Enroll(string subject, int num, string season, int year, string uid)
        {
            var getIds = from e in db.Enrollments
                         select e.EnrollmentId;

            var max = getIds.Max();

            var sid = from s in db.Students
                      where s.UId == uid
                      select s.StudentId;

            var cid = from c in db.Courses
                      where c.Dept == subject && c.Number == num.ToString()
                      join cl in db.Classes
                      on c.CatalogId equals cl.CatalogId
                      into join1
                      from j1 in join1
                      where j1.Semester == season + year.ToString()
                      select j1.ClassId;

            Enrollments enrollments = new Enrollments();
            enrollments.Class = cid.First();
            enrollments.Student = sid.First();
            enrollments.Grade = null;

            var enrollId = max + 1;
            enrollments.EnrollmentId = enrollId;

            try
            {
                db.Enrollments.Add(enrollments);
                db.SaveChanges();
            }
            catch (Exception ex)
            {
                Debug.Write(ex);
                return Json(new { success = false });
            }
            return Json(new { success = true });
        }



        /// <summary>
        /// Calculates a student's GPA
        /// A student's GPA is determined by the grade-point representation of the average grade in all their classes.
        /// Assume all classes are 4 credit hours.
        /// If a student does not have a grade in a class ("--"), that class is not counted in the average.
        /// If a student is not enrolled in any classes, they have a GPA of 0.0.
        /// Otherwise, the point-value of a letter grade is determined by the table on this page:
        /// https://advising.utah.edu/academic-standards/gpa-calculator-new.php
        /// </summary>
        /// <param name="uid">The uid of the student</param>
        /// <returns>A JSON object containing a single field called "gpa" with the number value</returns>
        public IActionResult GetGPA(string uid)
        {
            Dictionary<string, double> grades = new Dictionary<string, double>()
            {
                {"A", 4.0 },
                {"A-", 3.7 },
                {"B+", 3.3 },
                {"B", 3.0 },
                {"B-", 2.7 },
                {"C+", 2.3 },
                {"C", 2.0 },
                {"C-", 1.7 },
                {"D+", 1.3 },
                {"D", 1.0 },
                {"D-", 0.7 },
                {"F", 0.0 }
            };

            var query = from s in db.Students
                        where s.UId == uid
                        join e in db.Enrollments
                        on s.StudentId equals e.Student
                        into join1
                        from j1 in join1
                        select j1.Grade;

            var count = query.Count();
            var sum = 0.0;

            foreach (var q in query)
            {
                 if (q != null)
                {
                    var gradeVal = grades[q];
                    sum += gradeVal;
                }
                else
                {
                    count -= 1;
                }
            }

            var gpa = sum / count;

            var to_return = new GPA(gpa);

            return Json(to_return);
        }

        /*******End code to modify********/

    }
}