using System;
using System.Collections.Generic;

namespace LMS.Models.LMSModels
{
    public partial class Students
    {
        public Students()
        {
            Enrollments = new HashSet<Enrollments>();
            Submissions = new HashSet<Submissions>();
        }

        public int StudentId { get; set; }
        public string UId { get; set; }
        public string Major { get; set; }

        public virtual Departments MajorNavigation { get; set; }
        public virtual Users U { get; set; }
        public virtual ICollection<Enrollments> Enrollments { get; set; }
        public virtual ICollection<Submissions> Submissions { get; set; }
    }
}
