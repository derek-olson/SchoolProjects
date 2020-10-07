using System;
using System.Collections.Generic;

namespace LMS.Models.LMSModels
{
    public partial class Submissions
    {
        public int SubmissionId { get; set; }
        public int Student { get; set; }
        public int Assignment { get; set; }
        public string Contents { get; set; }
        public int? Score { get; set; }
        public DateTime Time { get; set; }

        public virtual Assignments AssignmentNavigation { get; set; }
        public virtual Students StudentNavigation { get; set; }
    }
}
