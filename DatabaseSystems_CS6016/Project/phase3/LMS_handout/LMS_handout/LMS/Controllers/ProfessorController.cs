using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Threading.Tasks;
using LMS.Helpers;
using LMS.Models.LMSModels;
using Microsoft.AspNetCore.Authorization;
using Microsoft.AspNetCore.Mvc;

namespace LMS.Controllers
{
    [Authorize(Roles = "Professor")]
    public class ProfessorController : CommonController
    {


        public IActionResult Index()
        {
            return View();
        }

        public IActionResult Students(string subject, string num, string season, string year)
        {
            ViewData["subject"] = subject;
            ViewData["num"] = num;
            ViewData["season"] = season;
            ViewData["year"] = year;
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

        public IActionResult Categories(string subject, string num, string season, string year)
        {
            ViewData["subject"] = subject;
            ViewData["num"] = num;
            ViewData["season"] = season;
            ViewData["year"] = year;
            return View();
        }

        public IActionResult CatAssignments(string subject, string num, string season, string year, string cat)
        {
            ViewData["subject"] = subject;
            ViewData["num"] = num;
            ViewData["season"] = season;
            ViewData["year"] = year;
            ViewData["cat"] = cat;
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

        public IActionResult Submissions(string subject, string num, string season, string year, string cat, string aname)
        {
            ViewData["subject"] = subject;
            ViewData["num"] = num;
            ViewData["season"] = season;
            ViewData["year"] = year;
            ViewData["cat"] = cat;
            ViewData["aname"] = aname;
            return View();
        }

        public IActionResult Grade(string subject, string num, string season, string year, string cat, string aname, string uid)
        {
            ViewData["subject"] = subject;
            ViewData["num"] = num;
            ViewData["season"] = season;
            ViewData["year"] = year;
            ViewData["cat"] = cat;
            ViewData["aname"] = aname;
            ViewData["uid"] = uid;
            return View();
        }

        /*******Begin code to modify********/


        /// <summary>
        /// Returns a JSON array of all the students in a class.
        /// Each object in the array should have the following fields:
        /// "fname" - first name
        /// "lname" - last name
        /// "uid" - user ID
        /// "dob" - date of birth
        /// "grade" - the student's grade in this class
        /// </summary>
        /// <param name="subject">The course subject abbreviation</param>
        /// <param name="num">The course number</param>
        /// <param name="season">The season part of the semester for the class the assignment belongs to</param>
        /// <param name="year">The year part of the semester for the class the assignment belongs to</param>
        /// <returns>The JSON array</returns>
        public IActionResult GetStudentsInClass(string subject, int num, string season, int year)
        {
            var query = from c in db.Courses
                        where c.Dept == subject && c.Number == num.ToString()
                        join cl in db.Classes
                        on c.CatalogId equals cl.CatalogId
                        into join1
                        from j1 in join1
                        where j1.Semester == season + year.ToString()
                        join e in db.Enrollments
                        on j1.ClassId equals e.Class
                        into join2
                        from j2 in join2
                        join s in db.Students
                        on j2.Student equals s.StudentId
                        into join3
                        from j3 in join3
                        join u in db.Users
                        on j3.UId equals u.UId
                        into join4
                        from j4 in join4
                        select new { fname = j4.FirstName, lname = j4.LastName, uid = j4.UId, dob = j4.Dob, grade = j2.Grade };
            return Json(query.ToArray());
        }



        /// <summary>
        /// Returns a JSON array with all the assignments in an assignment category for a class.
        /// If the "category" parameter is null, return all assignments in the class.
        /// Each object in the array should have the following fields:
        /// "aname" - The assignment name
        /// "cname" - The assignment category name.
        /// "due" - The due DateTime
        /// "submissions" - The number of submissions to the assignment
        /// </summary>
        /// <param name="subject">The course subject abbreviation</param>
        /// <param name="num">The course number</param>
        /// <param name="season">The season part of the semester for the class the assignment belongs to</param>
        /// <param name="year">The year part of the semester for the class the assignment belongs to</param>
        /// <param name="category">The name of the assignment category in the class, 
        /// or null to return assignments from all categories</param>
        /// <returns>The JSON array</returns>
        public IActionResult GetAssignmentsInCategory(string subject, int num, string season, int year, string category)
        { 

            var query1 = from c in db.Courses
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
                        select j2;

            if(category != null)
            {
                var query2 = from q in query1
                             where q.Name == category
                             select q;

                var query3 = from q2 in query2
                             join a in db.Assignments
                             on q2.CategoryId equals a.Category
                             into join3
                             from j3 in join3
                             select new { aname = j3.Name, cname = q2.Name, due = j3.DueDate, submissions = (from s in db.Submissions where s.Assignment == j3.AssignmentId select s).Count() };
                return Json(query3.ToArray());
            }
            else
            {
                var query2 = query1;

                var query3 = from q2 in query2
                             join a in db.Assignments
                             on q2.CategoryId equals a.Category
                             into join3
                             from j3 in join3
                             select new { aname = j3.Name, cname = q2.Name, due = j3.DueDate, submissions = (from s in db.Submissions where s.Assignment == j3.AssignmentId select s).Count() };
                return Json(query3.ToArray());
            }

        }


        /// <summary>
        /// Returns a JSON array of the assignment categories for a certain class.
        /// Each object in the array should have the folling fields:
        /// "name" - The category name
        /// "weight" - The category weight
        /// </summary>
        /// <param name="subject">The course subject abbreviation</param>
        /// <param name="num">The course number</param>
        /// <param name="season">The season part of the semester for the class the assignment belongs to</param>
        /// <param name="year">The year part of the semester for the class the assignment belongs to</param>
        /// <param name="category">The name of the assignment category in the class</param>
        /// <returns>The JSON array</returns>
        public IActionResult GetAssignmentCategories(string subject, int num, string season, int year)
        {
            var query = from c in db.Courses
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
                        select new { name = j2.Name, weight = j2.GradingWeight };
            return Json(query.ToArray());
        }

        /// <summary>
        /// Creates a new assignment category for the specified class.
        /// If a category of the given class with the given name already exists, return success = false.
        /// </summary>
        /// <param name="subject">The course subject abbreviation</param>
        /// <param name="num">The course number</param>
        /// <param name="season">The season part of the semester for the class the assignment belongs to</param>
        /// <param name="year">The year part of the semester for the class the assignment belongs to</param>
        /// <param name="category">The new category name</param>
        /// <param name="catweight">The new category weight</param>
        /// <returns>A JSON object containing {success = true/false} </returns>
        public IActionResult CreateAssignmentCategory(string subject, int num, string season, int year, string category, int catweight)
        {
            var getIds = from ac in db.AssignmentCategories
                         select ac.CategoryId;

            var max = getIds.Max();

            var query = from c in db.Courses
                        where c.Dept == subject && c.Number == num.ToString()
                        join cl in db.Classes
                        on c.CatalogId equals cl.CatalogId
                        into join1
                        from j1 in join1
                        where j1.Semester == season + year.ToString()
                        select j1.ClassId;

            AssignmentCategories assignmentCategories = new AssignmentCategories();
            assignmentCategories.ClassId = query.First();
            assignmentCategories.Name = category;
            assignmentCategories.GradingWeight = catweight;
            var catID = max + 1;
            assignmentCategories.CategoryId = catID;
            try
            {
                db.AssignmentCategories.Add(assignmentCategories);
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
        /// Creates a new assignment for the given class and category.
        /// </summary>
        /// <param name="subject">The course subject abbreviation</param>
        /// <param name="num">The course number</param>
        /// <param name="season">The season part of the semester for the class the assignment belongs to</param>
        /// <param name="year">The year part of the semester for the class the assignment belongs to</param>
        /// <param name="category">The name of the assignment category in the class</param>
        /// <param name="asgname">The new assignment name</param>
        /// <param name="asgpoints">The max point value for the new assignment</param>
        /// <param name="asgdue">The due DateTime for the new assignment</param>
        /// <param name="asgcontents">The contents of the new assignment</param>
        /// <returns>A JSON object containing success = true/false</returns>
        public IActionResult CreateAssignment(string subject, int num, string season, int year, string category, string asgname, int asgpoints, DateTime asgdue, string asgcontents)
        {
            var getIds = from a in db.Assignments
                         select a.AssignmentId;

            var max = getIds.Max();

            var query = from c in db.Courses
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
                        select j2.CategoryId;

            Assignments assignments = new Assignments();
            assignments.Category = query.First();
            assignments.Name = asgname;
            assignments.MaxPointVal = asgpoints;
            assignments.DueDate = asgdue;
            assignments.Contents = asgcontents;
            var assignID = max + 1;
            assignments.AssignmentId = assignID;
            try
            {
                db.Assignments.Add(assignments);
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
        /// Gets a JSON array of all the submissions to a certain assignment.
        /// Each object in the array should have the following fields:
        /// "fname" - first name
        /// "lname" - last name
        /// "uid" - user ID
        /// "time" - DateTime of the submission
        /// "score" - The score given to the submission
        /// 
        /// </summary>
        /// <param name="subject">The course subject abbreviation</param>
        /// <param name="num">The course number</param>
        /// <param name="season">The season part of the semester for the class the assignment belongs to</param>
        /// <param name="year">The year part of the semester for the class the assignment belongs to</param>
        /// <param name="category">The name of the assignment category in the class</param>
        /// <param name="asgname">The name of the assignment</param>
        /// <returns>The JSON array</returns>
        public IActionResult GetSubmissionsToAssignment(string subject, int num, string season, int year, string category, string asgname)
        {
            var query = from c in db.Courses
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
                        join a in db.Assignments
                        on j2.CategoryId equals a.Category
                        into join3
                        from j3 in join3
                        where j3.Name == asgname
                        join s in db.Submissions
                        on j3.AssignmentId equals s.Assignment
                        into join4
                        from j4 in join4
                        join st in db.Students
                        on j4.Student equals st.StudentId
                        into join5
                        from j5 in join5
                        join u in db.Users
                        on j5.UId equals u.UId
                        into join6
                        from j6 in join6
                        select new { fname = j6.FirstName, lname = j6.LastName, uid = j6.UId, time = j4.Time, score = j4.Score };
                     

            return Json(query.ToArray());
        }


        /// <summary>
        /// Set the score of an assignment submission
        /// </summary>
        /// <param name="subject">The course subject abbreviation</param>
        /// <param name="num">The course number</param>
        /// <param name="season">The season part of the semester for the class the assignment belongs to</param>
        /// <param name="year">The year part of the semester for the class the assignment belongs to</param>
        /// <param name="category">The name of the assignment category in the class</param>
        /// <param name="asgname">The name of the assignment</param>
        /// <param name="uid">The uid of the student who's submission is being graded</param>
        /// <param name="score">The new score for the submission</param>
        /// <returns>A JSON object containing success = true/false</returns>
        public IActionResult GradeSubmission(string subject, int num, string season, int year, string category, string asgname, string uid, int score)
        {
            var sid = from c in db.Courses
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
                      join a in db.Assignments
                      on j2.CategoryId equals a.Category
                      into join3
                      from j3 in join3
                      where j3.Name == asgname
                      join s in db.Submissions
                      on j3.AssignmentId equals s.Assignment
                      into join4
                      from j4 in join4
                      select j4;

            

            try
            {
                sid.First().Score = score;
                db.SaveChanges();

                Helper helper = new Helper();
                var g = helper.CalculateGrade(subject, num, season, year, uid);
                helper.UpdateGrade(g, uid, subject, num, season, year);
            }
            catch(Exception ex)
            {
                Debug.Write(ex);
                return Json(new { success = false });
            }
            return Json(new { success = true });



        }


        /// <summary>
        /// Returns a JSON array of the classes taught by the specified professor
        /// Each object in the array should have the following fields:
        /// "subject" - The subject abbreviation of the class (such as "CS")
        /// "number" - The course number (such as 5530)
        /// "name" - The course name
        /// "season" - The season part of the semester in which the class is taught
        /// "year" - The year part of the semester in which the class is taught
        /// </summary>
        /// <param name="uid">The professor's uid</param>
        /// <returns>The JSON array</returns>
        public IActionResult GetMyClasses(string uid)
        {
            var query = from p in db.Professors
                        where p.UId == uid
                        join c in db.Classes
                        on p.ProfessorId equals c.Professor
                        into join1
                        from j1 in join1
                        join cr in db.Courses
                        on j1.CatalogId equals cr.CatalogId
                        into join2
                        from j2 in join2
                        select new { subject = j2.Dept, j2.Number, j2.Name, season = j1.Semester.Substring(0, j1.Semester.Length - 4), year = j1.Semester.Substring(j1.Semester.Length - 4, 4) };

            return Json(query.ToArray());
        }


        /*******End code to modify********/

    }
}