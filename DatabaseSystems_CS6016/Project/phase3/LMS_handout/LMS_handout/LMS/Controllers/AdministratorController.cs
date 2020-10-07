using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using LMS.Models.LMSModels;
using Microsoft.AspNetCore.Authorization;
using Microsoft.AspNetCore.Mvc;

namespace LMS.Controllers
{
    [Authorize(Roles = "Administrator")]
    public class AdministratorController : CommonController
    {
        int incrementer = 1000;
        public IActionResult Index()
        {
            return View();
        }

        public IActionResult Department(string subject)
        {
            ViewData["subject"] = subject;
            return View();
        }

        public IActionResult Course(string subject, string num)
        {
            ViewData["subject"] = subject;
            ViewData["num"] = num;
            return View();
        }

        /*******Begin code to modify********/

        /// <summary>
        /// Returns a JSON array of all the courses in the given department.
        /// Each object in the array should have the following fields:
        /// "number" - The course number (as in 5530)
        /// "name" - The course name (as in "Database Systems")
        /// </summary>
        /// <param name="subject">The department subject abbreviation (as in "CS")</param>
        /// <returns>The JSON result</returns>
        public IActionResult GetCourses(string subject)
        {
            var query = from c in db.Courses
                        where c.Dept == subject
                        select new { c.Number, c.Name };
            return Json(query.ToArray());
        }





        /// <summary>
        /// Returns a JSON array of all the professors working in a given department.
        /// Each object in the array should have the following fields:
        /// "lname" - The professor's last name
        /// "fname" - The professor's first name
        /// "uid" - The professor's uid
        /// </summary>
        /// <param name="subject">The department subject abbreviation</param>
        /// <returns>The JSON result</returns>
        public IActionResult GetProfessors(string subject)
        {
            var query = from p in db.Professors
                        where p.Dept == subject
                        join u in db.Users
                        on p.UId equals u.UId
                        into join1
                        from j1 in join1
                        select new { j1.LastName, j1.FirstName, j1.UId };
            return Json(query.ToArray());
        }



        /// <summary>
        /// Creates a course.
        /// A course is uniquely identified by its number + the subject to which it belongs
        /// </summary>
        /// <param name="subject">The subject abbreviation for the department in which the course will be added</param>
        /// <param name="number">The course number</param>
        /// <param name="name">The course name</param>
        /// <returns>A JSON object containing {success = true/false}.
        /// false if the course already exists, true otherwise.</returns>
        public IActionResult CreateCourse(string subject, int number, string name)
        {
            incrementer += 1;
            Courses courses = new Courses();
            courses.Dept = subject;
            courses.Number = number.ToString();
            courses.Name = name;
            courses.CatalogId = incrementer.ToString();

            
            try
            {
                db.Add(courses);
                db.SaveChanges();
            }
            catch (Exception exception )
            {
                Console.WriteLine(exception);
                return Json(new { success = false });
            }

            return Json(new { success = true });
        }



        /// <summary>
        /// Creates a class offering of a given course.
        /// </summary>
        /// <param name="subject">The department subject abbreviation</param>
        /// <param name="number">The course number</param>
        /// <param name="season">The season part of the semester</param>
        /// <param name="year">The year part of the semester</param>
        /// <param name="start">The start time</param>
        /// <param name="end">The end time</param>
        /// <param name="location">The location</param>
        /// <param name="instructor">The uid of the professor</param>
        /// <returns>A JSON object containing {success = true/false}. 
        /// false if another class occupies the same location during any time 
        /// within the start-end range in the same semester, or if there is already
        /// a Class offering of the same Course in the same Semester,
        /// true otherwise.</returns>
        public IActionResult CreateClass(string subject, int number, string season, int year, DateTime start, DateTime end, string location, string instructor)
        {
            Classes classes = new Classes();
            
            classes.Semester = season + "_" + year.ToString();
            classes.StartTime = start.TimeOfDay;
            classes.EndTime = end.TimeOfDay;
            classes.Location = location;

            var catalog_query = from crs in db.Courses
                                where crs.Number == number.ToString() && crs.Dept == subject
                                select crs.CatalogId;

            classes.CatalogId = catalog_query.ToString();

            var instructor_query = from ins in db.Professors
                                   where ins.UId == instructor
                                   select ins.ProfessorId;
            classes.Professor = instructor_query.First();

            if (catalog_query.Count() == 0 || instructor_query.Count() == 0)
            {
                return Json(new { success = false });
            }
            
            try
            {
                db.Add(classes);
                db.SaveChanges();
            }
            catch (Exception exception)
            {
                Console.WriteLine(exception);
                return Json(new { success = false });
            }

            return Json(new { success = true });
        }


        /*******End code to modify********/

    }
}