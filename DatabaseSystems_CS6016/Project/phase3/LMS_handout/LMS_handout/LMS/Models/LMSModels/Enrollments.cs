using System;
using System.Collections.Generic;

namespace LMS.Models.LMSModels
{
    public partial class Enrollments
    {
        public int EnrollmentId { get; set; }
        public int Student { get; set; }
        public int Class { get; set; }
        public string Grade { get; set; }

        public virtual Classes ClassNavigation { get; set; }
        public virtual Students StudentNavigation { get; set; }
    }
}
