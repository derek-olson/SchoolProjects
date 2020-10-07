using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using LMS.Models.LMSModels;
using Microsoft.AspNetCore.Mvc;
using Microsoft.EntityFrameworkCore;

namespace LMS.Controllers
{
    public class CommonController : Controller
    {

        /*******Begin code to modify********/

        // TODO: Uncomment and change 'X' after you have scaffoled


        protected Team12LMSContext db;

        public CommonController()
        {
            db = new Team12LMSContext();
        }


        /*
         * WARNING: This is the quick and easy way to make the controller
         *          use a different LibraryContext - good enough for our purposes.
         *          The "right" way is through Dependency Injection via the constructor 
         *          (look this up if interested).
        */

        // TODO: Uncomment and change 'X' after you have scaffoled

        public void UseLMSContext(Team12LMSContext ctx)
        {
            db = ctx;
        }

        protected override void Dispose(bool disposing)
        {
            if (disposing)
            {
                db.Dispose();
            }
            base.Dispose(disposing);
        }




        /// <summary>
        /// Retreive a JSON array of all departments from the database.
        /// Each object in the array should have a field called "name" and "subject",
        /// where "name" is the department name and "subject" is the subject abbreviation.
        /// </summary>
        /// <returns>The JSON array</returns>
        public IActionResult GetDepartments()
        {
            // TODO: Do not return this hard-coded array.
            var query = from d in db.Departments select new {d.Name, d.Dept };
            return Json(query.ToArray());
        }



        /// <summary>
        /// Returns a JSON array representing the course catalog.
        /// Each object in the array should have the following fields:
        /// "subject": The subject abbreviation, (e.g. "CS")
        /// "dname": The department name, as in "Computer Science"
        /// "courses": An array of JSON objects representing the courses in the department.
        ///            Each field in this inner-array should have the following fields:
        ///            "number": The course number (e.g. 5530)
        ///            "cname": The course name (e.g. "Database Systems")
        /// </summary>
        /// <returns>The JSON array</returns>
        public IActionResult GetCatalog()
        {
            //List<Catalog> catalog = new List<Catalog>();
            var depts = from d in db.Departments
                        select new { subject = d.Dept, dname = d.Name, courses = from c in db.Courses where c.Dept == d.Dept select new { number = c.Number, cname = c.Name } };

            return Json(depts.ToArray());
        }

        /// <summary>
        /// Returns a JSON array of all class offerings of a specific course.
        /// Each object in the array should have the following fields:
        /// "season": the season part of the semester, such as "Fall"
        /// "year": the year part of the semester
        /// "location": the location of the class
        /// "start": the start time in format "hh:mm:ss"
        /// "end": the end time in format "hh:mm:ss"
        /// "fname": the first name of the professor
        /// "lname": the last name of the professor
        /// </summary>
        /// <param name="subject">The subject abbreviation, as in "CS"</param>
        /// <param name="number">The course number, as in 5530</param>
        /// <returns>The JSON array</returns>
        public IActionResult GetClassOfferings(string subject, int number)
        {
            var query = from c in db.Courses
                        where c.Dept == subject && c.Number == number.ToString()
                        join cl in db.Classes
                        on c.CatalogId equals cl.CatalogId
                        into join1
                        from j1 in join1
                        join p in db.Professors
                        on j1.Professor equals p.ProfessorId
                        into join2
                        from j2 in join2
                        join u in db.Users
                        on j2.UId equals u.UId
                        into join3
                        from j3 in join3
                        select new { season = j1.Semester.Substring(0, j1.Semester.Length - 4), year = j1.Semester.Substring(j1.Semester.Length - 4, 4), j1.Location, start = j1.StartTime, end = j1.EndTime, fname = j3.FirstName, lname = j3.LastName };
                        

            return Json(query.ToArray());
        }

        /// <summary>
        /// This method does NOT return JSON. It returns plain text (containing html).
        /// Use "return Content(...)" to return plain text.
        /// Returns the contents of an assignment.
        /// </summary>
        /// <param name="subject">The course subject abbreviation</param>
        /// <param name="num">The course number</param>
        /// <param name="season">The season part of the semester for the class the assignment belongs to</param>
        /// <param name="year">The year part of the semester for the class the assignment belongs to</param>
        /// <param name="category">The name of the assignment category in the class</param>
        /// <param name="asgname">The name of the assignment in the category</param>
        /// <returns>The assignment contents</returns>
        public IActionResult GetAssignmentContents(string subject, int num, string season, int year, string category, string asgname)
        {
            var query = from c in db.Courses
                        where c.Dept == subject && c.Number == num.ToString()
                        join cl in db.Classes
                        on c.CatalogId equals cl.CatalogId
                        into join1
                        from j1 in join1
                        where j1.Semester == season + year.ToString()
                        join a in db.AssignmentCategories
                        on j1.ClassId equals a.ClassId
                        into join2
                        from j2 in join2
                        where j2.Name == category
                        join asg in db.Assignments
                        on j2.CategoryId equals asg.Category
                        into join3
                        from j3 in join3
                        where j3.Name == asgname
                        select new { j3.Contents };

            return Content(query.First().Contents);
        }


        /// <summary>
        /// This method does NOT return JSON. It returns plain text (containing html).
        /// Use "return Content(...)" to return plain text.
        /// Returns the contents of an assignment submission.
        /// Returns the empty string ("") if there is no submission.
        /// </summary>
        /// <param name="subject">The course subject abbreviation</param>
        /// <param name="num">The course number</param>
        /// <param name="season">The season part of the semester for the class the assignment belongs to</param>
        /// <param name="year">The year part of the semester for the class the assignment belongs to</param>
        /// <param name="category">The name of the assignment category in the class</param>
        /// <param name="asgname">The name of the assignment in the category</param>
        /// <param name="uid">The uid of the student who submitted it</param>
        /// <returns>The submission text</returns>
        public IActionResult GetSubmissionText(string subject, int num, string season, int year, string category, string asgname, string uid)
        {
            var sid = from s in db.Students
                      where s.UId == uid
                      select s.StudentId;

          var query = from c in db.Courses
                        where c.Dept == subject && c.Number == num.ToString()
                        join cl in db.Classes
                        on c.CatalogId equals cl.CatalogId
                        into join1
                        from j1 in join1
                        where j1.Semester == season + year.ToString()
                        join a in db.AssignmentCategories
                        on j1.ClassId equals a.ClassId
                        into join2
                        from j2 in join2
                        where j2.Name == category
                        join asg in db.Assignments
                        on j2.CategoryId equals asg.Category
                        into join3
                        from j3 in join3
                        where j3.Name == asgname
                        join sub in db.Submissions
                        on j3.AssignmentId equals sub.Assignment
                        into join4
                        from j4 in join4
                        where j4.Student == sid.First()
                        select new { j4.Contents };
            if (query.Count() < 1)
            {

                return Content(null);
            }

            return Content(query.First().Contents);
        }


        /// <summary>
        /// Gets information about a user as a single JSON object.
        /// The object should have the following fields:
        /// "fname": the user's first name
        /// "lname": the user's last name
        /// "uid": the user's uid
        /// "department": (professors and students only) the name (such as "Computer Science") of the department for the user. 
        ///               If the user is a Professor, this is the department they work in.
        ///               If the user is a Student, this is the department they major in.    
        ///               If the user is an Administrator, this field is not present in the returned JSON
        /// </summary>
        /// <param name="uid">The ID of the user</param>
        /// <returns>
        /// The user JSON object 
        /// or an object containing {success: false} if the user doesn't exist
        /// </returns>
        public IActionResult GetUser(string uid)
        {
            var sq = from u in db.Users
                     where u.UId == uid
                     join s in db.Students
                     on u.UId equals s.UId
                     into join1
                     from j1 in join1
                     select new { fname = u.FirstName, lname = u.LastName, uid = j1.UId, department = j1.Major };

            var pq = from u in db.Users
                     where u.UId == uid
                     join p in db.Professors
                     on u.UId equals p.UId
                     into join1
                     from j1 in join1
                     select new { fname = u.FirstName, lname = u.LastName, uid = j1.UId, department = j1.Dept };

            var aq = from u in db.Users
                     where u.UId == uid
                     join a in db.Administrators
                     on u.UId equals a.UId
                     into join1
                     from j1 in join1
                     select new { fname = u.FirstName, lname = u.LastName, uid = j1.UId };

            if (sq.Count() > 0)
            {
                return Json(sq.First());
            }
            else if (pq.Count() > 0)
            {
                return Json(pq.First());
            }
            else if (aq.Count() > 0)
            {
                return Json(aq.First());
            }
            else
            {
                return Json(new { success = false });
            }
            
        }


        /*******End code to modify********/

    }
}