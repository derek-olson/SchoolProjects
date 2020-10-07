using System;
using System.Collections.Generic;

namespace LMS.Models.LMSModels
{
    public partial class Administrators
    {
        public int AdminId { get; set; }
        public string Role { get; set; }
        public string UId { get; set; }

        public virtual Users U { get; set; }
    }
}
