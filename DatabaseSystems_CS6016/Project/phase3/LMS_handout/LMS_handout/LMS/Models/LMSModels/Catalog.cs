using System;
using Microsoft.AspNetCore.Mvc;

namespace LMS.Models.LMSModels
{
    public class Catalog
    {
        public string subject;
        public string dname;
        private JsonResult courses;

        public Catalog(string dept, string name, JsonResult courses)
        {
            this.subject = dept;
            this.dname = name;
            this.courses = courses;
        }
    }
}
