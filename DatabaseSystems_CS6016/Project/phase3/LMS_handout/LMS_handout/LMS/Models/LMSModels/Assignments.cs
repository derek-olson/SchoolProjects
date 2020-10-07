using System;
using System.Collections.Generic;

namespace LMS.Models.LMSModels
{
    public partial class Assignments
    {
        public Assignments()
        {
            Submissions = new HashSet<Submissions>();
        }

        public int AssignmentId { get; set; }
        public string Name { get; set; }
        public int MaxPointVal { get; set; }
        public string Contents { get; set; }
        public DateTime DueDate { get; set; }
        public int Category { get; set; }

        public virtual AssignmentCategories CategoryNavigation { get; set; }
        public virtual ICollection<Submissions> Submissions { get; set; }
    }
}
